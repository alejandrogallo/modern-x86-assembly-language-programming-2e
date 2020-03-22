.intel_syntax noprefix

// extern "C" unsigned int IntegerLogical_(unsigned int a, unsigned int b, unsigned int c,  unsigned int d);

.data

.extern g_Val1

.text
.global IntegerLogical_

// Calculate (((a & b) | c ) ^ d) + g_Val1
IntegerLogical_:

  // edi = a & b
  and edi, esi
  // edi = (a & b) | c
  or edi, edx
  // edi = ((a & b) | c) ^ d
  xor edi, ecx
  // edi = (((a & b) | c) ^ d) + g_Val1
  add edi, [g_Val1]

  // eax = final result
  mov eax, edi
  // return to caller
  ret
