#include <iostream>
#include <iomanip>
#include <algorithm>
#include "lib/1D-functions.h"

using namespace std;

int **createArray(const int, const int);
void freeMemory(int**&, const int, const int);
void initArray(int**, const int, const int, int = 10, int = -10);
void printArray(int**, const int, const int);
void swapMaxAndMinColumns(int **, const int, const int);

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
  cout << "Enter N, M: "; cin >> N >> M;
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

void printArray(int **arr, const int N, const int M)
{
  for (int i = 0; i < M; i++)
  {
    for (int j = 0; j < N; j++)
      cout << setw(3) << arr[j][i] << " ";
    cout << '\n';
  }
}

void swapMaxAndMinColumns(int **arr, const int N, const int M)
{ 
  int max, min, count;
  int indexOfMax = 0, indexOfMin = 0;

  for (int i = 0; i < M; i++)
    if (abs(arr[0][i]) % 2)
      count++;

  max = min = count;

  for (int i = 1; i < N; i++)
  {
    count = 0;
    for (int j = 0; j < M; j++)
      if (abs(arr[i][j]) % 2)
        count++;

    if (count > max)
    {
      indexOfMax = i;
      max = count;
    }

    if (count < min)
    {
      indexOfMin = i;
      min = count;
    }
  }

  swap(arr[indexOfMin], arr[indexOfMax]);
}