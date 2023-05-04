#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

extern char __executable_start;

int sender(int a, int b, int c) {
  printf("sender(%d, %d, %d) called!", a, b, c);
  return 0;
}

void generate_payload() {
  int i = 5;
  int product = 1;
  while (i > 0) {
    product += product*i;
    i--;
  }
  __asm__ ("mov 0x4(%rsp), %edi");
  __asm__ ("mov 0x8(%rsp), %esi");
  __asm__ ("pop %r11");
  __asm__ ("pop %r12");
}

void spoof_mac_address() {
  __asm__ ("pop %rbx");
  __asm__ ("pop %r12");
  __asm__ ("mov 0x4(%rsp), %edx");
  __asm__ ("pop %r13");
}

void exploit(char* stack) {
  size_t buffer[1] = {0xFF};
  int i = 0;
  while (buffer[i] != (size_t) __builtin_return_address(0)) i++;
  char* token = strtok(stack, "|");
  while (token != NULL) {
    #ifdef __PIE__
      buffer[i] = (size_t) (strtol(token, NULL, 16) + &__executable_start);
    #else
      buffer[i] = (size_t) strtol(token, NULL, 16);
    #endif
    token = strtok(NULL, "|");
    i++;
  }
}

int main(int argc, char *argv[]) {
  if (argc != 2) exit(0);
  signal(SIGSEGV, exit);
  exploit(argv[1]);
  return 0;
}