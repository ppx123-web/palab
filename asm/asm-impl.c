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
          "mov %%rdi,%%rax;"
          "shr %%cl,%%rax;"
          "and $0x1,%%eax;"
          "add %%eax,%%edx;"
          "add $0x1,%%ecx;"
          "c,p $0x40,%%ecx;"
          "jne .loop;"
          "mov %%edx,%%eax;"
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
