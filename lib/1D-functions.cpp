#include <iostream>
#include <time.h>
#include "1D-functions.h"

using namespace std;

void createArray(int *&arr, const int N) {
  arr = new int[N];
}

int* createArray(const int N) {
  return new int[N];
}

void freeMemory(int *&arr, const int N) {
  delete[] arr;
}

void initArray(int arr[], const int N, int A, int B)
{
  srand(time(NULL));

  if (A > B) swap(A, B);
  
  double k1 = (B - A) * 1.0 / (RAND_MAX);
  
  for (int i = 0; i < N; i++)
    arr[i] = k1* rand() + A;
}

void printArray(int arr[], const int N)
{
  for (int i = 0; i < N; ++i)
    cout << arr[i] << " ";
  cout << '\n';
}

int indexOfMax(int arr[], int N)
{
  int maxIndex = 0;

  for (int i = 1; i < N; i++)
    if (arr[i] > arr[maxIndex]) maxIndex = i;

  return maxIndex;
}

int indexOfMin(int arr[], int N)
{
  int minIndex = 0;

  for (int i = 1; i < N; i++)
    if (arr[i] < arr[minIndex]) minIndex = i;
  
  return minIndex;
}

void inputArray(int arr[], const int N)
{
  for (int i = 0; i < N; ++i) cin >> arr[i];
}

int findMax(int arr[], int N)
{
  int max = arr[0];

  for (int i = 1; i < N; i++)
    if (arr[i] > max)
      max = arr[i];
  
  return max;
}

int findMin(int arr[], int N)
{
  int min = arr[0];

  for (int i = 1; i < N; i++)
    if (arr[i] < min)
  
      min = arr[i];
  return min;
}

void findMaxMin(int arr[], int N, int &min, int &max)
{
  min = max = arr[0];

  for (int i = 1; i < N; i++)
  {
    if (arr[i] < min) min = arr[i];
    if (arr[i] > max) max = arr[i];
  }
}

int getSum(int arr[], int N)
{
  int sum = 0;

  for (int i = 0; i < N; i++)
    sum += arr[i];
  
  return sum;
}

void howManyMaxMin(int arr[], const int N, int &countOfMax, int &countOfMin)
{
  int min, max;

  countOfMax = countOfMin = 0;
  min = max = arr[0];
  
  for (int i = 1; i < N; i++)
  {
    if (arr[i] < min)
    {
      min = arr[i];
      countOfMin = 1;
    }
    else if (arr[i] == min) countOfMin++;
    
    if (arr[i] > max)
    {
      max = arr[i];
      countOfMax = 1;
    }
    else if (arr[i] == max) countOfMax++;
  }
}

int howMany(int arr[], const int N, int n)
{
  int count = 0;
 
  for (int i = 0; i < N; i++)
    if (arr[i] == n) count++;

  return count;
}

void divArray(int A[], const int N, int B[], int C[])
{
  for (int i = 0, k = 0, j = 0; i < N; ++i)
  {
    if (A[i] > 0)
    {
      B[j] = A[i], j++;
    }
    if (A[i] < 0)
    {
      C[k] = A[i], k++;
    }
  }
}

void halfArray(int A[], const int N, int B[], int C[])
{
  int r = N / 2;
  for (int i = 0; i < r; ++i) B[i] = A[i];
  for (int i = 0; r + i < N; ++i) C[i] = A[r + i];
}

void reverse(int arr[], const int N)
{
  for (int i = 0; i < N / 2; i++)
    swap(arr[i], arr[N - 1 - i]);
}

void shiftRight(int arr[], const int N)
{
  int* temp = new int[N];

  for (int i = 0; i < N; ++i)
    temp[(i + 1) % N] = arr[i];
  
  for (int i = 0; i < N; ++i)
    arr[i] = temp[i];
}

void shiftLeft(int arr[], const int N)
{
  int* temp = new int[N];

  for (int i = 0; i < N; i++)
    temp[i] = arr[(i + 1) % N];
  
  for (int i = 0; i < N; i++)
    arr[i] = temp[i];
}
