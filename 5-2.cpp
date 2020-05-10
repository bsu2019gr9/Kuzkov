#include <iostream>
#include <fstream>
#include <time.h>
#include "Vector3D.h"

using namespace std;

typedef Vector3D ObjType;

ObjType* createArray(const size_t size)
{
    try
    {
        return new ObjType[size];
    }
    catch (bad_alloc& err)
    {
        return nullptr;
    }
}

void freeMemory(ObjType arr[])
{
    if (arr)
        delete[] arr;
}

void sort(ObjType arr[], const size_t size)
{
    for (size_t i = 1; i < size; i++)
    {
        for (size_t j = i; j > 0 && arr[j] < arr[j - 1]; j--)
        {
            swap(arr[j], arr[j - 1]);
        }
    }
}

ObjType max(ObjType arr[], const size_t size)
{
    ObjType max = arr[0];

    for (size_t i = 0; i < size; i++)
        if (max < arr[i])
            max = arr[i];
    
    return max;
}

ObjType min(ObjType arr[], const size_t size)
{
    ObjType min = arr[0];
 
    for (size_t i = 0; i < size; i++)
        if (min > arr[i])
            min = arr[i];
 
    return min;
}

int findIndexOf(ObjType arr[], const size_t size, ObjType item)
{
    for (size_t i = 0; i < size; i++)
        if (item == arr[i])
            return i;

    return -1;
}

void inputArray(ObjType arr[], const size_t size, istream &in_stream = cin)
{
    for (size_t i = 0; i < size; i++)
        in_stream >> arr[i];
}

void outputArray(ObjType arr[], const size_t size, ostream &out_stream = cout)
{
    for (size_t i = 0; i < size; i++)
        out_stream << arr[i];
}

void initArray(ObjType arr[], size_t size)
{
    srand(time(NULL));

    for (size_t i = 0; i < size; i++)
        arr[i] = ObjType(rand() % 100, rand() % 100, rand() % 100);
}

ObjType sum(ObjType arr[], size_t size)
{
    ObjType result;

    for (size_t i = 0; i < size; i++)
        result += arr[i];
    
    return result;
}

int main()
{
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    const size_t SIZE = 3;

    ObjType arr[SIZE];

    inputArray(arr, SIZE);
    outputArray(arr, SIZE);

    inputArray(arr, SIZE, fin);
    outputArray(arr, SIZE, fout);

    cout << sum(arr, SIZE) << "\n";

    sort(arr, SIZE);

    outputArray(arr, SIZE);
    outputArray(arr, SIZE, fout);

    ObjType *arr2 = createArray(SIZE);

    initArray(arr2, SIZE);
    outputArray(arr2, SIZE);

    freeMemory(arr2);

    return 0;
}