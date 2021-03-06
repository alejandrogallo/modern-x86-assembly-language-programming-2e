//------------------------------------------------
//               Ch13_05.cpp
//------------------------------------------------

#include "stdafx.h"
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <limits>
#include "ZmmVal.h"

using namespace std;

extern "C" void Avx512PackedCompareF32_(const ZmmVal* a, const ZmmVal* b, uint16_t c[8]);

const char* c_CmpStr[8] =
{
    "EQ", "NE", "LT", "LE", "GT", "GE", "ORDERED", "UNORDERED"
};

void ToZmmVal(ZmmVal des[8], uint16_t src[8])
{
    for (size_t i = 0; i < 8; i++)
    {
        uint16_t val_src = src[i];

        for (size_t j = 0; j < 16; j++)
            des[i].m_U32[j] = val_src & (1 << j) ? 1 : 0;
    }
}

void Avx512PackedCompareF32(void)
{
    alignas(64) ZmmVal a;
    alignas(64) ZmmVal b;
    uint16_t c[8];

    a.m_F32[0] = 2.0;       b.m_F32[0] = 1.0;
    a.m_F32[1] = 7.0;       b.m_F32[1] = 12.0;
    a.m_F32[2] = -6.0;      b.m_F32[2] = -6.0;
    a.m_F32[3] = 3.0;       b.m_F32[3] = 8.0;

    a.m_F32[4] = -2.0;      b.m_F32[4] = 1.0;
    a.m_F32[5] = 17.0;      b.m_F32[5] = 17.0;
    a.m_F32[6] = 6.5;       b.m_F32[6] = -9.125;
    a.m_F32[7] = 4.875;     b.m_F32[7] = numeric_limits<float>::quiet_NaN();

    a.m_F32[8] = 2.0;       b.m_F32[8] = 101.0;
    a.m_F32[9] = 7.0;       b.m_F32[9] = -312.0;
    a.m_F32[10] = -5.0;     b.m_F32[10] = 15.0;
    a.m_F32[11] = -33.0;    b.m_F32[11] = -33.0;

    a.m_F32[12] = -12.0;    b.m_F32[12] = 198.0;
    a.m_F32[13] = 107.0;    b.m_F32[13] = 107.0;
    a.m_F32[14] = 16.125;   b.m_F32[14] = -2.75;
    a.m_F32[15] = 42.875;   b.m_F32[15] = numeric_limits<float>::quiet_NaN();

    Avx512PackedCompareF32_(&a, &b, c);

    cout << "\nResults for Avx512PackedCompareF32\n";

    ZmmVal c_display[8];

    ToZmmVal(c_display, c);

    for (int sel = 0; sel < 4; sel++)
    {
        cout << setw(12) << "a[" << sel << "]:" << a.ToStringF32(sel) << '\n';
        cout << setw(12) << "b[" << sel << "]:" << b.ToStringF32(sel) << '\n';
        cout << '\n';

        for (int j = 0; j < 8; j++)
            cout << setw(14) << c_CmpStr[j] << ':' << c_display[j].ToStringU32(sel)  << '\n';
        cout << '\n';
    }
}

int main()
{
    Avx512PackedCompareF32();
    return 0;
}
