//------------------------------------------------
//               Ch13_02.cpp
//------------------------------------------------

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <array>
#include <random>

using namespace std;

extern "C" bool Avx512CalcValues_(double* c, const double* a, const double* b, size_t n);

template<typename T> void Init(T* x, size_t n, unsigned int seed)
{
    uniform_int_distribution<> ui_dist {1, 200};
    default_random_engine rng {seed};

    for (size_t i = 0; i < n; i++)
        x[i] = (T)(ui_dist(rng) - 25);
}

bool Avx512CalcValuesCpp(double* c, const double* a, const double* b, size_t n)
{
    if (n == 0)
        return false;

    for (size_t i = 0; i < n; i++)
    {
        double val = a[i] * b[i];
        c[i] = (val >= 0.0) ? sqrt(val) : val * val;
    }

    return true;
}

int main()
{
    const size_t n = 20;
    array<double, n> a;
    array<double, n> b;
    array<double, n> c1;
    array<double, n> c2;

    Init<double>(a.data(), n, 13);
    Init<double>(b.data(), n, 23);

    bool rc1 = Avx512CalcValuesCpp(c1.data(), a.data(), b.data(), n);
    bool rc2 = Avx512CalcValues_(c2.data(), a.data(), b.data(), n);

    if (!rc1 || !rc2)
    {
        cout << "Invalid return code - ";
        cout << "rc1 = " << boolalpha << rc1 << "  ";
        cout << "rc2 = " << boolalpha << rc2 << '\n';
    }
    else
    {
        cout << fixed << setprecision(4);

        for (size_t i = 0; i < n; i++)
        {
            cout << "i:  " << setw(2) << i << "  ";
            cout << "a:  " << setw(9) << a[i] << "  ";
            cout << "b:  " << setw(9) << b[i] << "  ";
            cout << "c1: " << setw(13) << c1[i] << "  ";
            cout << "c2: " << setw(13) << c2[i] << "\n";
        }
    }
}
