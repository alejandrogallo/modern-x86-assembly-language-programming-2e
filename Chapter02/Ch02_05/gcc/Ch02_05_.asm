/*
  extern "C" int64_t IntegerMul_( int8_t a, int16_t b, int32_t c
                                , int64_t d, int8_t e, int16_t f
                                , int32_t g, int64_t h);
*/
.intel_syntax noprefix

.data
.global IntegerMul_

IntegerMul_:

  movsx rax, dil        /* rax = sign_extend(a) */
  movsx rsi, sil        /* rax = sign_extend(a) */
  imul rax, rsi

  movsx rdx, edx
  imul rax, rdx

  imul rax, rcx
  movsx r8, r8b
  imul rax, r8

  movsx r9, r9w
  imul rax, r9

  movsxd rdx, dword ptr [rsp + 8]
  imul rax, rdx

  // this is 8 + 8 because when we push the values it is in 64 bit mode,
  // so we push 64 bit registers into stack, therefore the next values should
  // be 8 byte further
  imul rax, qword ptr [rsp + 16]

  ret

/*
  extern "C" int UnsignedIntegerDiv_( uint8_t a, uint16_t b, uint32_t c
                                    , uint64_t d, uint8_t e, uint16_t f
                                    , uint32_t g, uint64_t h, uint64_t* quo
                                    , uint64_t* rem
                                    );
*/

.global UnsignedIntegerDiv_

UnsignedIntegerDiv_:

  /*  Calculate a + b + c + d */
  movzx rax, dil /* rax <- 8-bit a */
  movzx rdi, si
  add rax, rdi

  movsxd rdx, edx
  add rax, rdx
  add rax, rcx
  xor rdx, rdx

  /*  Calculate e + f + g + h */
  movzx r8, r8b
  movzx r9, r9w
  add r8, r9
  mov r9d, dword ptr [rsp + 8]
  movsxd r9, r9d
  add r8, r9
  add r8, qword ptr [rsp + 16]

  jz zero_denominator /* jump if r8 is zero */

  div r8

  mov rcx, [rsp + 24]
  mov [rcx], rax
  mov rcx, [rsp + 32]
  mov [rcx], rdx

  mov rax, 1
  ret

zero_denominator:
  xor rax, rax
  ret

