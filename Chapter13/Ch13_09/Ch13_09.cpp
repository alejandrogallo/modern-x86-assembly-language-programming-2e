//------------------------------------------------
//               Ch13_09.cpp
//------------------------------------------------

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include "Ch13_09.h"
#include "AlignedMem.h"

using namespace std;

extern "C" const int c_NumPtsMin = 32;
extern "C" const int c_NumPtsMax = 16 * 1024 * 1024;
extern "C" const int c_KernelSizeMin = 3;
extern "C" const int c_KernelSizeMax = 15;
unsigned int g_RngSeedVal = 97;

void Avx512Convolve2(void)
{
    const int n1 = 512;
    const float kernel[] { 0.0625f, 0.25f, 0.375f, 0.25f, 0.0625f };
    const int ks = sizeof(kernel) / sizeof(float);
    const int ks2 = ks / 2;
    const int n2 = n1 + ks2 * 2;
    const unsigned int alignment = 64;

    // Create signal array
    AlignedArray<float> x1_aa(n1, alignment);
    AlignedArray<float> x2_aa(n2, alignment);
    float* x1 = x1_aa.Data();
    float* x2 = x2_aa.Data();

    CreateSignal(x1, n1, ks, g_RngSeedVal);
    PadSignal(x2, n2, x1, n1, ks2);

    // Perform convolutions
    AlignedArray<float> y5_aa(n1, alignment);
    AlignedArray<float> y6_aa(n1, alignment);
    float* y5 = y5_aa.Data();
    float* y6 = y6_aa.Data();

    bool rc5 = Avx512Convolve2_(y5, x2, n1, kernel, ks);
    bool rc6 = Avx512Convolve2Ks5_(y6, x2, n1, kernel, ks);

    cout << "Results for Convolve2\n";
    cout << "  rc5 = " << boolalpha << rc5 << '\n';
    cout << "  rc6 = " << boolalpha << rc6 << '\n';

    if (!rc5 || !rc6)
        return;

    // Save data
    const char* fn = "Ch13_09_Convolve2Results.csv";
    ofstream ofs(fn);

    if (ofs.bad())
        cout << "File create error - " << fn << '\n';
    else
    {
        const char* delim = ", ";

        ofs << fixed << setprecision(7);
        ofs << "i, x1, y5, y6\n";

        for (int i = 0; i < n1; i++)
        {
            ofs << setw(5) << i << delim;
            ofs << setw(10) << x1[i] << delim;
            ofs << setw(10) << y5[i] << delim;
            ofs << setw(10) << y6[i] << '\n';
        }

        ofs.close();
        cout << "\nResults data saved to file " << fn << '\n';
    }
}

int main()
{
    int ret_val = 1;

    try
    {
        Avx512Convolve2();
        Avx512Convolve2_BM();
        ret_val = 0;
    }

    catch (runtime_error& rte)
    {
        cout << "run_time exception has occurred\n";
        cout << rte.what() << '\n';
    }

    catch (...)
    {
        cout << "Unexpected exception has occurred\n";
    }

    return ret_val;
}
