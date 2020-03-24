//
// extern "C" int IntegerMulDiv_(int a, int b, int* prod, int* quo, int* rem)//
//
// Returns:      0 = error (divisor equals zero), 1 = success
//

.intel_syntax noprefix

.data
.global IntegerMulDiv_

IntegerMulDiv_:

  mov eax, esi

  or eax, eax
  jz InvalidDivisorSection

  imul eax, edi
  mov [rdx], eax

  // cdq basically takes eax -> edx:eax
  mov eax, edi
  cdq
  idiv esi

  mov [rcx], eax
  mov [r8], edx

InvalidDivisorSection:
  ret
