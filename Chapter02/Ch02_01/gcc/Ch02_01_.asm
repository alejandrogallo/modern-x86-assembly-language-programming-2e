.intel_syntax noprefix

// Note: in the book this does not work for the gnu assembler, i.e.,
// the order is different, for instance for PrintResult it would be
//
//                     edi, esi, edx, ecx, r8d, r9d
//    PrintResult("Test 1", a  , b  , c  , d  , result);
//
// and for IntegerAddSub_ it would be
//
//                          edi, esi, edx  ecx
//  result = IntegerAddSub_(a  , b  , c  , d  );
//
// which makes sense because further would be in the stack

.text

.global IntegerAddSub_
IntegerAddSub_:
  xor rax, rax
  add eax, edi
  add eax, esi
  add eax, edx
  sub eax, ecx
  ret

.global SimpleSum_
SimpleSum_:

  xor rax, rax
  add rax, rdi
  add rax, rsi
  ret

