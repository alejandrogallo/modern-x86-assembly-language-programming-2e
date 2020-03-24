#include <iostream>

using namespace std;

extern "C" int IntegerMulDiv_(int a, int b, int* prod, int* quo, int* rem);

void PrintResult(const char* s, int rc, int a, int b, int p, int q, int r)
{
    const char nl = '\n';

    cout << s << nl;
    cout << "a = " << a << ", b = " << b << ", rc = " << rc << nl;

    if (rc != 0)
      cout << "prod = " << p << ", quo = " << q << ", rem = " << r << nl;
    else
      cout << "prod = " << p << ", quo = undefined" << ", rem = undefined" << nl;

    std::cout << std::endl;
}

int IntegerMulDiv(int a, int b, int *prod, int *quo, int *rem) {
  if (b == 0) return 0;
  *prod = a * b;
  *rem = a % b;
  *quo = a / b;
  return 1;
}

int main()
{
    int rc;
    int a, b;
    int prod, quo, rem;

    a = 47;
    b = 13;
    prod = quo = rem = 0;
    rc = IntegerMulDiv_(a, b, &prod, &quo, &rem);
    std::cout << "\x1b[33m";
    PrintResult("Test 1", rc, a, b, prod, quo, rem);

    std::cout << "\x1b[32m";
    rc = IntegerMulDiv(a, b, &prod, &quo, &rem);
    PrintResult("in c++", rc, a, b, prod, quo, rem);

    a = -291;
    b = 7;
    prod = quo = rem = 0;
    rc = IntegerMulDiv_(a, b, &prod, &quo, &rem);

    std::cout << "\x1b[33m";
    PrintResult("Test 2", rc, a, b, prod, quo, rem);
    std::cout << "\x1b[32m";
    rc = IntegerMulDiv(a, b, &prod, &quo, &rem);
    PrintResult("in c++", rc, a, b, prod, quo, rem);

    a = 19;
    b = 0;
    prod = quo = rem = 0;
    rc = IntegerMulDiv_(a, b, &prod, &quo, &rem);

    std::cout << "\x1b[33m";
    PrintResult("Test 3", rc, a, b, prod, quo, rem);
    std::cout << "\x1b[32m";
    rc = IntegerMulDiv(a, b, &prod, &quo, &rem);
    PrintResult("in c++", rc, a, b, prod, quo, rem);

    a = 247;
    b = 85;
    prod = quo = rem = 0;
    rc = IntegerMulDiv_(a, b, &prod, &quo, &rem);

    std::cout << "\x1b[33m";
    PrintResult("Test 4", rc, a, b, prod, quo, rem);
    std::cout << "\x1b[32m";
    rc = IntegerMulDiv(a, b, &prod, &quo, &rem);
    PrintResult("in c++", rc, a, b, prod, quo, rem);

    std::cout << "\x1b[0m";
    return 0;
}

