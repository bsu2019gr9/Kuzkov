#include <iostream>
#include <iomanip>
#include <algorithm>
#include "lib/1D-functions.h"

using namespace std;

int **createArray(const int, const int);
void freeMemory(int**&, const int, const int);
void initArray(int**, const int, const int, int = 10, int = -10);
void printArray(int**, const int, const int, const int = 3);
void swapMaxAndMinColumns(int **, const int, const int);
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

  int N, M;
  cout << "Enter cols, rows: "; cin >> N >> M;
  int **arr = createArray(N, M);

  initArray(arr, N, M);
  cout << "Current array: " << endl;
  printArray(arr, N, M);
  cout << endl;

  swapMaxAndMinColumns(arr, N, M);

  cout << "Swapped: " << endl;
  printArray(arr, N, M);

  freeMemory(arr, N, M);

  return 0;
}

int **createArray(const int N, const int M)
{
  int **arr = new int*[N];
  for (int i = 0; i < N; i++)
    arr[i] = new int[M];
  return arr;
}

void freeMemory(int **&arr, const int N, const int M)
{
  for (int i = 0; i < N; i++)
  {
    delete[] arr[i];
    arr[i] = nullptr;
  }
  delete[] arr;
  arr = nullptr;
}

void initArray(int **arr, const int N, const int M, int A, int B)
{
  if (A > B) swap(A, B);
  
  double k1 = (B - A) * 1.0 / RAND_MAX;
  
  for (int i = 0; i < N; i++)
    for (int j = 0; j < M; j++)
      arr[i][j] = k1 * rand() + A;
}

void printArray(int **arr, const int N, const int M, const int columnSize)
{
  for (int i = 0; i < M; i++)
  {
    for (int j = 0; j < N; j++)
      cout << setw(columnSize) << arr[j][i] << " ";
    cout << endl;
  }
}

void swapMaxAndMinColumns(int **arr, const int N, const int M)
{ 
  int max, min;
  int **pmax, **pmin;

  max = min = getCountOfOdd(*arr, *arr + M);
  pmin = pmax = arr;

  for (int **p = arr + 1; p < arr + N; p++)
  {
    int count = getCountOfOdd(*p, *p + M);

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

  swap(*pmax, *pmin);
}

int getCountOfOdd(int *begin, int *end)
{
  int count = 0;

  for (int *p = begin; p < end; p++)
    if (abs(*p) % 2)
      count++;
  
  return count;
}