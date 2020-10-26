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
  int s = 0,i = 0;
  asm(
    ".L1:"
    "shrl %%ecx,%%rbx;"
    "and $1,%%rbx;"
    "cmp $1,%%rbx;"
    "je .L2;"
    "incl %%eax;"
    ".L2:"
    "cmp $64,%%ecx;"
    "jl L1;"
    : "=c"(i),"=b"(x),"=a"(s)
    : "c"(i),"b"(x),"a"(s)
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
