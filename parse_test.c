#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include "parse_infix.h"
#include "lex_infix.h"

// test program
int main(int argc, char** argv)
{
  // determine whether trace mode is used or not
  int trace_mode = 0;
  int c;
  while ((c = getopt(argc, argv, "t")) != -1)
    if (c == 't') trace_mode = 1;

  while (1) {
    char buf[BUFSIZ];
    printf("> ");
    fgets(buf, BUFSIZ, stdin);
    buf[strlen(buf) - 1] = '\0';

    double value;
    if (strlen(buf) > 0) {
      value = parse(buf, trace_mode);
    }
    else  // no input to quit
      break;

    if (isParseNormal())
      printf("\t%f\n", value);
    else
      puts("\tinvalid expression!");
  }
  return 0;
}
