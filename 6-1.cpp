#include <iostream>
#include <stdio.h>
#include <cstring>
#include <stdint.h>
#include <cmath>

using namespace std;

typedef int16_t WORD;
typedef int32_t D_WORD;

typedef struct {
    D_WORD count;
    WORD count2;
} example;

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

int *loadBMP(const char*, int&, int&);
int saveBMP(const char*, int*, int, int);

int rgb(int, int, int);

void radialGradient(int, int, int, int*, int, int);

int main()
{
    int mx, my;
    int *data = loadBMP("file.bmp", mx, my);

    radialGradient(128, 128, 50, data, mx, my);

    saveBMP("file.bmp", data, mx, my);
    delete[] data;

    return 0;
}


int *loadBMP(const char *fname, int &mx, int &my)
{
    mx = my = -1;
    
    FILE *f = fopen(fname, "rb");

    if(!f)
        return nullptr;

    BMPheader bh;
    size_t res = fread(&bh, 1, sizeof(BMPheader), f);

    if(res != sizeof(BMPheader))
    {
        fclose(f);
        return nullptr;
    }

    if(bh.bfType!=0x4d42 && bh.bfType!=0x4349 && bh.bfType!=0x5450)
    { 
        fclose(f);
        return nullptr;
    }

    fseek(f, 0, SEEK_END);
    int filesize = ftell(f);
    fseek(f, sizeof(BMPheader), SEEK_SET);

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
        fclose(f); 
        return nullptr; 
    }

    mx = bh.biWidth;
    my = bh.biHeight;

    int mx3 = (3*mx+3) & (-4);

    unsigned char *tmp_buf = new unsigned char[mx3*my];
    res = fread(tmp_buf, 1, mx3*my, f);

    if((int)res != mx3*my)
    {
        delete []tmp_buf;
        fclose(f);
        return nullptr;
    }
    fclose(f); 

    int *v = new int[mx*my];

    unsigned char *ptr = (unsigned char *) v;
    for(int y = my-1; y >= 0; y--) {
        unsigned char *pRow = tmp_buf + mx3*y;
        for(int x=0; x< mx; x++) {
            *ptr++ = *(pRow + 2);
            *ptr++ = *(pRow + 1);
            *ptr++ = *pRow; 
            pRow+=3;
            ptr ++;
        }
    }
    delete []tmp_buf;
    return v;
}

int saveBMP(const char *fname, int *v, int mx, int my)
{
    BMPheader bh;
    memset( &bh, 0, sizeof(bh) );
    bh.bfType =0x4d42;
    int mx3 = (3*mx+3) & (-4);
    int filesize = 54 + my*mx3;
    bh.bfSize = filesize;
    bh.bfReserved =  0;
    bh.biPlanes   =  1;
    bh.biSize     = 40;
    bh.bfOffBits  = 14 + bh.biSize;
    bh.biWidth    = mx;
    bh.biHeight   = my;
    bh.biBitCount = 24;
    bh.biCompression= 0;

    FILE *f = fopen( fname, "wb" );
    if( !f ) return -1;
    size_t res;

    res = fwrite( &bh, 1, sizeof(BMPheader), f );
    if( res != sizeof(BMPheader) ) { fclose(f); return -1; }

    unsigned char *tmp_buf = new unsigned char[mx3*my];
    unsigned char *ptr = (unsigned char *) v;
    for(int y = my-1; y >= 0; y--) {
        unsigned char *pRow = tmp_buf + mx3*y;
        for(int x=0; x< mx; x++) {
            *(pRow + 2) = *ptr++;
            *(pRow + 1) = *ptr++;
            *pRow       = *ptr++; 
            pRow+=3;
            ptr++;
        }
    }
    fwrite( tmp_buf, 1, mx3*my, f );
    fclose(f);
    delete []tmp_buf;
    return 0;
}

int rgb(int r, int g, int b)
{
    return (b << 8*2) | (g << 8) | r;
}

float dist(int x1, int y1, int x2, int y2)
{
    return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}

int lerp(int r1, int g1, int b1, int r2, int g2, int b2, float k)
{
    if (k > 1) k = 1;
    return rgb(
        (r2 - r1)*k + r1,
        (g2 - g1)*k + g1,
        (b2 - b1)*k + b1);
}

void radialGradient(int x, int y, int r, int *data, int mx, int my)
{
    for (int i = 0; i < my; i++)
    {
        for (int j = 0; j < mx; j++)
        {
            data[i*my + j] = lerp(255, 0, 0, 0, 0, 255, dist(i, j, x, y) / r);
        }
    }
}