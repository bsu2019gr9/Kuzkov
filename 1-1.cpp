#include <iostream>
#include <algorithm>
#include "lib/1D-functions.h"

using namespace std;

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

  int size;
  cout << "Enter size of array: "; cin >> size;
  int* arr = allocMemory(size);

  initArray(arr, size);

  cout << "Array: ";
  printArray(arr, size);

  sort(arr, arr + size);
  
  cout << "Sorted: ";
  printArray(arr, size);

  int count = 0, temp_count = 1;
  for (int *p = arr + 1; p < arr + size; p++)
  {
    if (*p == *(p-1))
      temp_count++;
    else
    {
      if (temp_count > 1)
        count++;
      temp_count = 1;
    }
  }
  if (temp_count > 1) count++;

  cout << "Count of repeating elements: " << count << endl;
  cout << endl;

  initArray(arr, size);

  cout << "Array: ";
  printArray(arr, size);

  sort(arr, arr + size);
  
  cout << "Sorted: ";
  printArray(arr, size);

  count = 0;
  temp_count = 1;
  for (int *p = arr + 1; p < arr + size; p++)
  {
    if (*p == *(p-1))
      temp_count++;
    else
    {
      if (temp_count > count)
        count = temp_count;
      temp_count = 1;
    }
  }
  if (temp_count > count) count = temp_count;

  cout << "Max count of equal elements: " << count << endl;

  freeMemory(arr, size);

  return 0;
}