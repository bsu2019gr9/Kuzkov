#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cstring>
#include <stdint.h>
#include <cmath>

using namespace std;

typedef uint8_t BYTE;
typedef int16_t WORD;
typedef int32_t D_WORD;

#pragma pack(push, 2)
struct BMPheader {
      WORD      bfType;
      D_WORD    bfSize;
      D_WORD    bfReserved;
      D_WORD    bfOffBits;

      D_WORD    biSize;

      D_WORD    biWidth;
      D_WORD    biHeight;
      WORD      biPlanes;
      WORD      biBitCount;
      D_WORD    biCompression;

      D_WORD    biSizeImage;

      D_WORD    biXPelsPerMeter;
      D_WORD    biYPelsPerMeter;
      D_WORD    biClrUsed;

      D_WORD    biClrImportant;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct RGB {
    BYTE R;
    BYTE G;
    BYTE B;

    RGB() : R(0), G(0), B(0)
    {}

    RGB(BYTE _R, BYTE _G, BYTE _B) : R(_R), G(_G), B(_B)
    {}
};
#pragma pack(pop)

template <typename T>
T** createArray2D (int, int);

template <typename T>
void deleteArray2D (T**, int, int);

RGB** loadBMP(const char*, int&, int&);
int saveBMP(const char*, RGB**, int, int);

double dist(int, int, int, int);
RGB lerp(const RGB&, const RGB&, double);

void radialGradient(int, int, int, const RGB&, const RGB&, RGB**, int, int);

int main()
{
    const int CANVAS_WIDTH  = 1024;
    const int CANVAS_HEIGHT = 1024;
    const int GRADIENT_RADIUS = 256;
    const RGB COLOR_FROM(255, 255, 255);
    const RGB COLOR_TO(0, 0, 0);

    RGB **data = createArray2D<RGB>(CANVAS_WIDTH, CANVAS_HEIGHT);

    radialGradient(
        CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, GRADIENT_RADIUS,
        COLOR_FROM, COLOR_TO,
        data, CANVAS_WIDTH, CANVAS_HEIGHT
    );

    saveBMP("res.bmp", data, CANVAS_WIDTH, CANVAS_HEIGHT);

    deleteArray2D<RGB>(data, CANVAS_WIDTH, CANVAS_HEIGHT);

    return 0;
}


template <typename T>
T** createArray2D (int rows, int columns)
{
    T **res = new T*[rows];
    for (T **it = res; it < res + rows; it++)
        *it = new T[columns];
    return res;
}

template <typename T>
void deleteArray2D (T **arr, int rows, int columns)
{
    for (T **it = arr; it < arr + rows; it++)
        delete[] *it;
    delete[] arr;
}



RGB** loadBMP(const char *fname, int &w, int &h)
{
    w = h = -1;
    
    ifstream fin;
    fin.open(fname, ios_base::binary);

    if(!fin.is_open())
        return nullptr;

    BMPheader bh;
    fin.read((char*) &bh, sizeof(bh));

    if (bh.bfType != 0x4d42 &&
        bh.bfType!=0x4349 &&
        bh.bfType!=0x5450)
    { 
        fin.close();
        return nullptr;
    }

    fin.seekg(0, ios_base::end);
    int filesize = fin.tellg();
    fin.seekg(sizeof(bh), ios_base::beg);

    if(bh.bfSize != filesize ||
       bh.bfReserved != 0 ||
       bh.biPlanes != 1 ||
       (bh.biSize != 40 && bh.biSize != 108 && bh.biSize != 124) ||
       bh.bfOffBits != 14 + bh.biSize ||
       bh.biWidth < 1 || bh.biWidth > 10000 ||
       bh.biHeight < 1 || bh.biHeight > 10000 ||
       bh.biBitCount != 24 ||
       bh.biCompression != 0) 
    {
        fin.close(); 
        return nullptr; 
    }

    w = bh.biWidth;
    h = bh.biHeight;

    const int BYTES_IN_ROW = sizeof(RGB) * w;

    RGB **data = createArray2D<RGB>(h, w);

    for (int i = h - 1; i >= 0; i--)
        fin.read((char*) data[i], BYTES_IN_ROW);

    return data;
}

int saveBMP(const char *fname, RGB **data, int w, int h)
{
    BMPheader bh;

    const int BYTES_IN_ROW = sizeof(RGB) * w;
    const int filesize = sizeof(BMPheader) + h * BYTES_IN_ROW;

    bh.bfType =0x4d42;
    bh.bfSize = filesize;
    bh.bfReserved = 0;
    bh.biPlanes = 1;
    bh.biSize = 40;
    bh.bfOffBits = 14 + bh.biSize;
    bh.biWidth = w;
    bh.biHeight = h;
    bh.biBitCount = 24;
    bh.biCompression= 0;

    ofstream fout;
    fout.open(fname, ios_base::binary);

    if (!fout.is_open())
        return -1;

    fout.write((char*) &bh, sizeof(bh));

    for(int i = h - 1; i >= 0; i--)
        fout.write((char*) data[i], BYTES_IN_ROW);

    fout.close();
    return 0;
}



double dist(int x1, int y1, int x2, int y2)
{
    return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}

RGB lerp(const RGB &from, const RGB &to, double k)
{
    if (k > 1) k = 1;

    return RGB(
        (to.R - from.R)*k + from.R,
        (to.G - from.G)*k + from.G,
        (to.B - from.B)*k + from.B
    );
}



void radialGradient(int x, int y, int r, const RGB &from, const RGB &to, RGB** data, int w, int h)
{
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
            data[i][j] = lerp(from, to, dist(i, j, x, y) / r);
}