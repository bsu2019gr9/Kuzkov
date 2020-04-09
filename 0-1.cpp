#include <iostream>
#include <iomanip>
#include <cmath>
#include "1D-functions.h"

using namespace std;

double arctg(double, double);
double exp(double, double);

/* 
 * Вычисление интегральных сумм
 * f(x) = arctg(x) + 2*e^x
 * eps  = 0.0001
 * a = 0, b = 1
 * h = 0.2
 */
int main() {
  int* arr = createArray(10);
  initArray(arr, 10);

  const int WIDTH = 10;
  const double EPS = 0.0001;
  double a = 0, b = 1, h = 0.2;

  cout << setw(WIDTH) << "x" << setw(WIDTH) << "f(x)" << setw(WIDTH) << "F(x)\n";

  for (double x = a; x <= b; x += h)
  {
    cout << setw(WIDTH) << x;
    cout << setw(WIDTH) << arctg(x, EPS) + 2 * exp(x, EPS);
    cout << setw(WIDTH) << atan(x) + 2 * exp(x) << "\n";
  }

  return 0;
}

double arctg(double x, double eps)
{
  double sum = x, prev_sum = 0, term = x;

  for (int i = 3; fabs(prev_sum - sum) > eps; i += 2)
  {
    prev_sum = sum;
    term *= -x * x;
    sum += term / i;
  }

  return sum;
}

double exp(double x, double eps)
{
  double sum = 1, term = 1;
  
  for (int i = 1; fabs(term) > eps; i++)
  {
    term *= x / i;
    sum += term;
  }

  return sum;
}