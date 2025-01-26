#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "lex_infix.h"
extern void displayToken(Token);

// Test bufferNext and BbufferBack
// Enter> text to be analyzed
// > command    [n: next, b: back, q: quit]

int main(void) {
  char buf[BUFSIZ];
  printf("Enter text> ");
  fgets(buf, BUFSIZ, stdin);
  buf[strlen(buf) - 1] = '\0';

  bufferInit(buf);
  printf("\t"); displayToken(bufferCurrentToken());

  while (1) {
    printf("> ");
    fgets(buf, BUFSIZ, stdin);
    buf[strlen(buf) - 1] = '\0';

    if (strcmp(buf, "q") == 0)
      break;
    else if (strcmp(buf, "n") == 0) {
      bufferNext();
      printf("\t"); displayToken(bufferCurrentToken());
    }
    else if (strcmp(buf, "b") == 0) {
      bufferBack();
      printf("\t"); displayToken(bufferCurrentToken());
    }
  }
}
