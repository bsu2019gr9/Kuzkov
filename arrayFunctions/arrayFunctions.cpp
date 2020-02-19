#include <iostream>
#include <time.h>

using namespace std;

int* giveMemory(int n = 10)
{
  return new int[n];
}

void freeMemory(int arr[])
{
  if (!arr)
  {
    cout << "Empty array\n";
    return;
  }

  delete[] arr;
}

int findIdMin(int arr[], int N)
{
  int minIndex = 0;

  for (int i = 1; i < N; i++)
    if (arr[i] < arr[minIndex]) minIndex = i;
  
  return minIndex;
}

int findIdMax(int arr[], int N)
{
  int maxIndex = 0;

  for (int i = 1; i < N; i++)
    if (arr[i] > arr[maxIndex]) maxIndex = i;

  return maxIndex;
}

void printArray(int arr[], const int N)
{
  for (int i = 0; i < N; ++i)
    cout << arr[i] << " ";
  cout << '\n';
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

int findSum(int arr[], int N)
{
  int sum = 0;

  for (int i = 0; i < N; i++)
    sum += arr[i];
  
  return sum;
}

void initArray(int arr[], const int N, int A = -10, int B = 10)
{
  srand(time(NULL));

  if (A > B) swap(A, B);
  
  double k1 = (B - A) * 1.0 / (RAND_MAX);
  
  for (int i = 0; i < N; i++)
    arr[i] = k1* rand() + A;
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

  return k;
}

void getPositiveNegativeArray(int arr[], const int N, int &neg, int &pos)
{
  neg = pos = 0;

  for (int i = 0; i < N; ++i)
  {
    if (arr[i] > 0) pos++;
    if (arr[i] < 0) neg++;
  }
}

void halfArray(int A[], const int N, int B[], int C[])
{
  int r = N / 2;
  for (int i = 0; i < r; ++i) B[i] = A[i];
  for (int i = 0; r + i < N; ++i) C[i] = A[r + i];
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

bool changeArray1(int arr[], const int N)
{
  bool flag = false;
  const int k = 999;
  for (int i = 0; i < N - 1; ++i)
  {
    if (arr[i])
    {
      arr[i + 1] = 999;
      flag = true;
      break;
    }
  }
  return flag;
}

bool changeArray2(int arr[], const int N)
{
  int min = findIdMin(arr, N);
  if (min + 1 < N - 1)
  {
    arr[min + 1] = 999;
    return true;
  }
  return false;
}

bool changeArray3(int arr[], const int N)
{
  int max = findIdMax(arr, N);

  if (max - 1 >= 0)
  {
    arr[max - 1] = 999;
    return true;
  }

  return false;
}

void reverse(int arr[], const int N)
{
  for (int i = 0; i < N / 2; ++i) swap(arr[i], arr[N - 1 - i]);
}

int findIdLastMin(int arr[], int N)
{
  int min = 0;
  for (int i = 1; i < N; i++)
    if (arr[i] <= arr[min]) min = i;
  return min;
}

int findIdFirstMax(int arr[], int N)
{
  int maxIndex = 0;
  
  for (int i = 1; i < N; i++)
    if (arr[i] > arr[maxIndex])
      maxIndex = i;

  return maxIndex;
}

int findSumIf(int arr[], int n)
{

  int sum = 0;
  int max = findIdFirstMax(arr, n);
  int min = findIdLastMin(arr, n);

  if (min - max <= 0)
  {
    cout << "min >= max";
    return 1;
  }
  for (int i = max + 1; i < min; ++i)
    sum += arr[i];
  
  return sum;
}

void moveRight(int arr[], const int N)
{
  int temp = new int[N];

  for (int i = 0; i < N; ++i)
    temp[(i + 1) % N] = arr[i];
  
  for (int i = 0; i < N; ++i)
    arr[i] = temp[i];
}

void moveLeft(int arr[], const int N)
{
  int temp = new int[N];

  for (int i = 0; i < N; ++i)
    temp[i] = arr[(i + 1) % N];
  
  for (int i = 0; i < N; ++i)
    arr[i] = temp[i];
}