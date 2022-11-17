#include <stdio.h>
#include <stdlib.h>

#define C_RESET "\x1b[0m"
#define C_RED "\x1b[31m"
#define C_GREEN "\x1b[32m"

void flush_in() {
  int ch;
  while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
  }
}