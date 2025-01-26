#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "lex_infix.h"

// ---- Lexical analysis ----
static Buffer buf; // target expression

int skipSpace(int index)
{
  for (; buf.sexpr[index] == ' ' || buf.sexpr[index] == '\t'; index++) ;
  return index;
}

// -- public functions --

void bufferInit(char* string)
{
  strcpy(buf.sexpr, string);
  buf.ind = 0;
  buf.previous = 0;
}

int bufferCurrentTokenLength(void);

void bufferNext(void)
{
  buf.previous = buf.ind;
  buf.ind += bufferCurrentTokenLength();
}

void bufferBack(void)
{
  buf.ind = buf.previous;
}

int bufferInd(void)
{
  return buf.ind;
}

Token bufferCurrentToken(void)
{
  Token t;
  t.value = 0;

  int index = buf.ind;
  index = skipSpace(index);

  if (buf.sexpr[index] == '+') {
    t.tid = plus;
  }
  else if (buf.sexpr[index] == '*') {
    t.tid = multiply;
  }
  else if (buf.sexpr[index] == '-') {
    t.tid = minus;
  }
  else if (buf.sexpr[index] == '/') {
    t.tid = substitute;
  }
  else if (buf.sexpr[index] == '(') {
    t.tid = left_parenthis;
  }
  else if (buf.sexpr[index] == ')') {
    t.tid = right_parenthis;
  }
  else if (isdigit(buf.sexpr[index])) {
    t.tid = number;
    while (isdigit(buf.sexpr[index])) {
      t.value = t.value * 10 + (double)(buf.sexpr[index] - '0');
      index++;
    }
  }
  else if (buf.sexpr[index] == 0) {
    t.tid = eos;
  }
  else {
    t.tid = other;
  }
  return t;
}

int bufferCurrentTokenLength(void)
{
  int index = buf.ind;
  index = skipSpace(index);

  if (isdigit(buf.sexpr[index])) {
    while (isdigit(buf.sexpr[index])) {
      index++;
    }
  }
  else if (buf.sexpr[index] != 0) {
    index++;
  }
  return index - buf.ind;
}

void displayToken(Token t)
{
  switch (t.tid) {
    case plus:
      printf("[+]");
      break;
    case multiply:
      printf("[*]");
      break;
    case minus:
      printf("[-]");
      break;
    case substitute:
      printf("[/]");
      break;
    case left_parenthis:
      printf("[(]");
      break;
    case right_parenthis:
      printf("[)]");
      break;
    case number:
      printf("[%f]", t.value);
      break;
    case other:
      printf("[x]");
      break;
    case eos:
      printf("[eos]");
      break;
  }
}
