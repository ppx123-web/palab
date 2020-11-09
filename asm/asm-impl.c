#include "asm.h"
#include <string.h>

int64_t asm_add(int64_t a, int64_t b) {
    asm(
      "addq %%rbx,%%rax;"
      : "=a"(a)
      : "a"(a), "b"(b)
      : 
  );
  return a;

}

int asm_popcnt(uint64_t x) {
  int s=0,i=0;
  asm(
      "movq $0,%%rcx;"
      "movq $0,%%rax;"
      "L:\n"
        "movq %%rdi,%%rdx;"
        "shrq %%cl,%%rdx;"
        "andq $0x1,%%rdx;"
        "addq %%rdx,%%rax;"
        "addq $1,%%rcx;"
        "cmp $0x40,%%rcx;"
        "jne L;"
        :"=a"(s)
        :"a"(s), "D"(x)
        :"rdx"
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
