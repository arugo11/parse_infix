#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "lex_infix.h"
#include "stack_tracer.h"
#include "parse_infix.h"

// Interpreter for mathematical expressions in Infix Notation
// Recursive descent parser
//
// expr := term | term {+ term} | term {- term}
// term := fact | fact {* fact} | fact {/ fact}
// fact := (expr) | number
double expr();
double term();
double fact();
int error = 0;

int isParseNormal(void)
{
  bufferNext();
  return bufferCurrentToken().tid == eos && !error;
}

double parse(char* target, int tm)
{
  trace_mode = tm;  // stack_traser on/off
  error = 0;  // initializing error flag
  bufferInit(target); // lexical analyzer starts

  return expr();
}
// ---- Modules for parsing and evaluating the target ----
// BNF
// expr := term | term {+ term} | term {- term}
double expr(void)
{
  stack_push("expr", bufferInd());

  double value;

  value = term();
  while (1) {
    bufferNext();
    Token t = bufferCurrentToken();
    if (t.tid == plus) {
        bufferNext();
        value += term();
    }
    else if (t.tid == minus) {
        bufferNext();
        value -= term();
    }
    else {
      bufferBack();
      break;
    }
  }
  stack_pop(value);
  return value;
}

// BNF
// term := fact | fact {* fact} | fact {/ fact}
double term(void)
{
  stack_push("term", bufferInd());
  double value = fact( );

  while (1) {
    bufferNext();
    Token t = bufferCurrentToken();
    if (t.tid == multiply) {
      bufferNext();
      value *= fact();
    }
    else if (t.tid == substitute) {
      bufferNext();
      value /= fact();
    }
    else {
      bufferBack();
      break;
    }
  }
  stack_pop(value);
  return value;
}

// BNF
// fact := (expr) | number
double fact(void)
{
  stack_push("fact", bufferInd());

  double value=0.0;
  Token t = bufferCurrentToken();

  if (t.tid == left_parenthis) {
      bufferNext();
      value = expr();
      bufferNext();
      Token t = bufferCurrentToken();
      if (t.tid != right_parenthis) {
        error = 1;
        puts("')' is missing.");
      }
  }
  else if (t.tid == number) {
      value = t.value;
  }
  else if (t.tid == other) {
    error = 1;
    puts("\tinvalid character!");
  }
  else if (t.tid == eos) {
    error = 1;
    puts("\tunexpected eos!");
  }
  stack_pop(value);
  return value;
 }
