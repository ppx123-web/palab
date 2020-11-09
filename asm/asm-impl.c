#include "asm.h"
#include <string.h>

int64_t asm_add(int64_t a, int64_t b) {
    asm(
      "addq %%rbx,%%rax;"
      : "=a"(a)
      : "a"(a), "b"(b)
      : //"rbx","rax"
  );
  return a;

}

int asm_popcnt(uint64_t x) {
  int s=0,i=0;
  asm(
      "movq $0,%rcx;"
      "movq $0,%rax;"
      "movq $0,%rdi;"
      "s:\n"
        "movq %rdi,%rdx;"
        "shrq %cl,%rdx;"
        "andq $0x1,%rdx;"
        "addq %rdx,%rax;"
        "addq $1,%rcx;"
        "cmpq $0x40,%rcx;"
        "jne s;"
        :"=a"(s)
        :d"(x)
        :"rcx","rax","rdi","rdx"
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
