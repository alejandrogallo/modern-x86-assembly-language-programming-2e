// extern "C" int
// IntegerShift_( unsigned int a
//              , unsigned int count
//              , unsigned int* a_shl
//              , unsigned int* a_shr
//              )
//
// Returns:      0 = error (count >= 32), 1 = success
//

.intel_syntax noprefix

.text
.global IntegerShift_

IntegerShift_:

  // the shl instruction seems to work only with the
  // 8-bit counter register cl.
  // That's why we exchange the contents of say
  // ecx and edi

  // a     = edi
  // count = esi
  // a_shl = rdx
  // a_shr = rcx
  // r8d and r9d are free

  xchg rcx, rsi

  // a     = edi
  // count = rcx
  // a_shl = rdx
  // a_shr = rsi

  // initialize eax to zero
  xor eax, eax

  cmp ecx, 31
  ja get_out

  // move a to r8d
  mov eax, edi
  shl eax, cl
  mov [rdx], eax

  // move a to r8d
  mov eax, edi
  shr eax, cl
  mov [rsi], eax

  mov eax, 1

// Just exit
get_out:
  // we could also use leave to restore the stack
  // state
  ret
