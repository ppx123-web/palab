#include "asm.h"
#include <string.h>

int64_t asm_add(int64_t a, int64_t b) {
    asm(
      "add %%ebx,%%eax;"
      : "=a"(a)
      : "a"(a), "b"(b)
  );
  return a;

}

int asm_popcnt(uint64_t x) {
  int s = 0,i = 0;
  asm(
    ".L1:"
    "shr %[t1],%[t2];"
    "and $1,%[t2];"
    "cmp $1,%[t2];"
    "je .L2;"
    "incl %[t3];"
    ".L2:"
    "cmp $64,%[t1];"
    "jl L1;"
    : [t1] "c"(i),[t2] "b"(x), [t3] "a"(s)
    : [t1] "c"(i),[t2] "b"(x), [t3] "a"(s)
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
