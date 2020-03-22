//------------------------------------------------
//               Ch02_01.cpp
//------------------------------------------------

#include <iostream>

using std::cout;
using std::endl;

extern "C" int IntegerAddSub_(int a, int b, int c, int d);
extern "C" int SimpleSum_(int a, int b);

void PrintResult(const char* msg, int a, int b, int c, int d, int result)
{
  cout << msg         << endl
       << "a = "      << a      << endl
       << "b = "      << b      << endl
       << "c = "      << c      << endl
       << "d = "      << d      << endl
       << "result = " << result << endl
       << endl
       ;
}

int main() {
    int a, b, c, d, result;

    a = 10; b = 20; c = 30; d = 18;
    result = IntegerAddSub_(a, b, c, d);
    PrintResult("Test 1", a, b, c, d, result);

    a = 101; b = 34; c = -190; d = 25;
    result = IntegerAddSub_(a, b, c, d);
    PrintResult("Test 2", a, b, c, d, result);

    std::cout << SimpleSum_(a, b) << std::endl;

    return 0;
}
