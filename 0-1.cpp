/* 
 * Вычисление интегральных сумм
 * f(x) = arctg(x) + 2*e^x
 * eps  = 0.0001
 * a = 0, b = 1
 * h = 0.2
 */

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

double arctg(double, double);
double exp(double, double);

int main() {
  const int WIDTH = 10;
  double a = 0, b = 1, eps = 0.0001, h = 0.2;

  cout << setw(WIDTH - 5) << "x" << setw(WIDTH) << "f(x)" << setw(WIDTH) << "F(x)\n";

  for (double x = a; x <= b; x += h)
  {
    cout << setw(WIDTH - 5) << x;
    cout << setw(WIDTH) << arctg(x, eps) + 2 * exp(x);
    cout << setw(WIDTH) << arctg(x, eps) + 2 * exp(x) << "\n";
  }

  system("pause");
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