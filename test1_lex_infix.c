#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "lex_infix.h"
extern void displayToken(Token);
// Test how input texts are analyzed
// > text to be analyzed
// > no text to quit

int main(void) {
  while (1) {
    char buf[BUFSIZ];
    printf("> ");
    fgets(buf, BUFSIZ, stdin);
    buf[strlen(buf) - 1] = '\0';

    double value;
    if (strlen(buf) > 0) {
      bufferInit(buf);
      Token t = bufferCurrentToken();
      while (t.tid != eos) {
        displayToken(t);
        bufferNext();
        t = bufferCurrentToken();
      }
      printf("\n");
    }
    else  // no input to quit
      break;
  }
  return 0;
}
