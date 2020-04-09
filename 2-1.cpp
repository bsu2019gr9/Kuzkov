#include <iostream>
#include <ctime>
#include "2D-functions.h"

using namespace std;

void findMaxAndMinColumns(int**, int**&, int**&, const int, const int);
int getCountOfOdd(int*, int*);

/* 
 * В массиве А(N,М) столбец с минимальным
 * количеством нечетных элементов поменять
 * местами с столбцом c максимальным
 * кол-вом таких элементов.
 * N - столбцы, M - строки.
 */
int main()
{
  srand(time(NULL));

  int M, N;
  cout << "Enter rows, cols: "; cin >> M >> N;
  cout << endl;

  int **arr = createArray(N, M);
  int **pmin, **pmax;

  initArray(arr, N, M);
  cout << "Current array: " << endl;
  printArray(arr, N, M);
  cout << endl;

  findMaxAndMinColumns(arr, pmin, pmax, N, M);
  swap(*pmin, *pmax);

  cout << "Swapped: " << endl;
  printArray(arr, N, M);

  freeMemory(arr, N, M);

  return 0;
}

void findMaxAndMinColumns(int **arr, int **&pmin, int **&pmax, const int M, const int N)
{ 
  int max, min;

  max = min = getCountOfOdd(*arr, *arr + M);
  pmin = pmax = arr;

  for (int **p = arr + 1; p < arr + M; p++)
  {
    int count = getCountOfOdd(*p, *p + N);

    if (count > max)
    {
      pmax = p;
      max = count;
    }

    if (count < min)
    {
      pmin = p;
      min = count;
    }
  }
}

int getCountOfOdd(int *begin, int *end)
{
  int count = 0;

  for (int *p = begin; p < end; p++)
    if (abs(*p) % 2)
      count++;
  
  return count;
}
