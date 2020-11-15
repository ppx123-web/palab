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
        :"rdx","rcx"
          );
  return s;
}

void *asm_memcpy(void *dest, const void *src, size_t n) {
  //return memcpy(dest, src, n);
  asm(
      "movq %%rdx,%%rax;" //src = rdi = rax
      "movq %%rdi,%%rsi;" //dest = rdx = rsi
      "movq $0,%%rcx;"
    "L1:\n"
      "movb (%%rax),%%dl;"
      "movb %%dl,(%%rsi);"
      "addq $1,%%rax;"
      "addq $1,%%rsi;"
      "addq $1,%%rcx;"
      "cmp %%rbx,%%rcx;"
      "jne L1;"
      "movq %%rdi,%%rax;"
      :"=a"(dest)
      :"d"(src),"D"(dest),"b"(n)
      :"rcx","rsi"
  );
  return dest;
}

int asm_setjmp(asm_jmp_buf env) {
    int ret;
    asm(
        "movq %%rax,(%%rdi);"
        "movq %%rbx,0x8(%%rdi);"
        "movq %%rcx,0x10(%%rdi);"
        "movq %%rdx,0x18(%%rdi);"
        "movq %%rdi,0x20(%%rdi);"
        "movq %%rsi,0x28(%%rdi);"
        "movq %%rbp,%%rbx;"
        "add $0x10,%%rbx;"
        "movq %%rbx,0x30(%%rdi);"
        "movq (%%rbp),%%rbx;"
        "movq %%rbx,0x38(%%rdi);"
        "movq 0x8(%%rbp),%%rbx;"
        "movq %%rbx,0x40(%%rdi);"
        "movl 0x48(%%rdi),%%eax"
        :"=D"(env),"=a"(ret)
        :
        :"rbx"
    );
    return ret;
}

void asm_longjmp(asm_jmp_buf env, int val) {
    asm(
        "movq %%rsi,%%rax;"
        "movq 0x10(%%rdi),%%rcx;"
        "movq 0x18(%%rdi),%%rdx;"
        "movq 0x30(%%rdi),%%rsp;"
        "movq 0x38(%%rdi),%%rbp;"
        "movq 0x40(%%rdi),%%rbx;"
        "pushq %%rbx;"
        "movq 0x8(%%rdi),%%rbx;"
        "movq 0x20(%%rdi),%%rdi;"
        "movq 0x28(%%rdi),%%rsi;"
        "ret;"
        :
        :"D"(env),"S"(val)
        :"rax","rcx","rbx"
    );
}
