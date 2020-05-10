#include <iostream>
#include <iomanip>
#include "2D-functions.h"

using namespace std;

int **createArray(const int M, const int N)
{
  int **arr = new int*[M];
  for (int i = 0; i < M; i++)
    arr[i] = new int[N];
  return arr;
}

void freeMemory(int **&arr, const int M, const int N)
{
  for (int i = 0; i < M; i++)
  {
    delete[] arr[i];
    arr[i] = nullptr;
  }
  delete[] arr;
  arr = nullptr;
}

void initArray(int **arr, const int M, const int N, int A, int B)
{
  if (A > B) swap(A, B);
  
  double k1 = (B - A) * 1.0 / RAND_MAX;
  
  for (int i = 0; i < M; i++)
    for (int j = 0; j < N; j++)
      arr[i][j] = k1 * rand() + A;
}

void printArray(int **arr, const int M, const int N, const int columnSize)
{
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < M; j++)
      cout << setw(columnSize) << arr[j][i] << " ";
    cout << endl;
  }
}
