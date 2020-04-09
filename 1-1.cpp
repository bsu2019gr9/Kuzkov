#include <iostream>
#include <ctime>
#include <algorithm>
#include "1D-functions.h"

using namespace std;

int countOfRepeatingElements(int[], const int);
int maxCountOfEqualElements(int[], const int);

/* 
 * 1. В массиве размера N, заполненного случ.числами
 * от -10 до 10, подсчитать количество элементов,
 * встречающихся более одного раза.
 *
 * 2. В массиве размера N, заполненного случ.числами
 * от -10 до 20, определить максимальную длину
 * последовательности равных элементов.
 */
int main()
{
  srand(time(NULL));

  int N;
  cout << "Enter size of array: "; cin >> N;
  int* arr = createArray(N);

  initArray(arr, N);

  cout << "Array: ";
  printArray(arr, N);

  sort(arr, arr + N);
  
  cout << "Sorted: ";
  printArray(arr, N);

  cout << "Count of repeating elements: " <<
    countOfRepeatingElements(arr, N) << endl;

  cout << "Max count of equal elements: " <<
    maxCountOfEqualElements(arr, N) << endl;

  freeMemory(arr, N);

  return 0;
}

int countOfRepeatingElements(int arr[], const int N)
{
    int res = 0, count = 1;

    for (int *p = arr + 1; p < arr + N; p++)
    {
      if (*p == *(p-1))
        count++;
      else
      {
        if (count > 1)
          res++;
        count = 1;
      }
    }
    if (count > 1) res++;
    
    return res;
}


int maxCountOfEqualElements(int arr[], const int N)
{
    int maxCount = 0, count = 1;

    for (int *p = arr + 1; p < arr + N; p++)
    {
      if (*p == *(p-1))
        count++;
      else
      {
        if (count > maxCount)
          maxCount = count;
        count = 1;
      }
    }
    if (count > maxCount) maxCount = count;
    
    return maxCount;
}