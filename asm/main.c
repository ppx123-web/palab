#include "asm.h"
#include <assert.h>
#include <stdio.h>

int main() {
  asm_jmp_buf buf;
  char* src[10]="abc";
  char* dst[10]={0};
  int r = asm_setjmp(buf);
  if (r == 0) {
    assert(asm_add(1234, 5678) == 6912);
    //assert(asm_add(1,2) == 3);
    //assert(asm_add(12313,123123) == 12313+123123);
    //assert(asm_popcnt(0x1)==1);
    //assert(asm_popcnt(0x0123456789abcdefULL) == 32);
    asm_memcpy(dst,src,3);
    assert(dst[0] == src[0]);
    // TODO: add more tests here.
    asm_longjmp(buf, 123);
  } else {
    assert(r == 123);
    printf("PASSED.\n");
  }
}
