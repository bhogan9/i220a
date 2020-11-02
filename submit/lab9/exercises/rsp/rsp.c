#include <stdio.h>

/** Return value of %rsp register just before return */
static void *
get_rsp(void)
{
  void *rsp;
  __asm__("movq %%rsp, %0": "=r"(rsp));
  return rsp;
}

int main() {
  int stkVar;
  printf("&stkVar = %p; rsp = %p\n", &stkVar, get_rsp());
  return 0;
}
