#include "asm.h"
#include <string.h>

int64_t asm_add(int64_t a, int64_t b) {
    asm(
      "add %%rbx,%%rax;"
      : "=a"(a)
      : "a"(a), "b"(b)
  );
  return a;

}

int asm_popcnt(uint64_t x) {
  int s = 0,i = 0,temp =0 ;
    for (int i = 0; i < 64; i++) {
        if ((x >> i) & 1) s++;
    }
  asm(
      ".loop:\n"
          "movl %2,%1;"
          "shr %3,%1;"
          "and $0x1,%1;"
          "add %1,%0;"
          "add $0x1,%3;"
          "cmp $0x40,%3;"
          "jne .loop;"
          :"=a"(s)
          :"r"(i),"r"(x),"r"(temp)
          :
//          : "%eax","%ecx","%edx"
          );
  return s;


}

void *asm_memcpy(void *dest, const void *src, size_t n) {
  return memcpy(dest, src, n);
}

int asm_setjmp(asm_jmp_buf env) {
  return setjmp(env);
}

void asm_longjmp(asm_jmp_buf env, int val) {
  longjmp(env, val);
}
