#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "lex_infix.h"
#include "stack_tracer.h"
#include "parse_infix.h"

// Interpreter for mathematical expressions in Infix Notation
// Recursive descent parser
//
// Modified grammar to handle unary minus:
// expr := term | term {+ term} | term {- term} | -expr
// term := fact | fact {* fact} | fact {/ fact}
// fact := (expr) | number | -fact
double expr();
double term();
double fact();
int error = 0;

// 演算子の種類を判定
int isOperator(enum TokenID tid) {
    return tid == plus || tid == minus || tid == multiply || tid == substitute;
}

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

double expr(void)
{
  stack_push("expr", bufferInd());

  double value;
  Token t = bufferCurrentToken();
  
  if (t.tid == minus) {
    // 連続するマイナスをチェック
    int minus_count = 1;
    Token next;
    do {
      bufferNext();
      next = bufferCurrentToken();
      if (next.tid == minus) {
        minus_count++;
      }
    } while (next.tid == minus);
    
    // 連続するマイナスの数に応じて符号を決定
    value = (minus_count % 2 == 0) ? term() : -term();
  } else {
    value = term();
    while (1) {
      bufferNext();
      t = bufferCurrentToken();
      if (t.tid == plus || t.tid == minus) {
        Token next;
        bufferNext();
        next = bufferCurrentToken();
        
        // 演算子の重複チェック
        if (isOperator(next.tid)) {
          error = 1;
          puts("Multiple operators not allowed");
          break;
        }
        bufferBack();
        
        if (t.tid == plus) {
          bufferNext();
          value += term();
        } else {
          bufferNext();
          value -= term();
        }
      } else {
        bufferBack();
        break;
      }
    }
  }
  
  stack_pop(value);
  return value;
}

double term(void)
{
  stack_push("term", bufferInd());
  double value = fact();

  while (1) {
    bufferNext();
    Token t = bufferCurrentToken();
    if (t.tid == multiply || t.tid == substitute) {
      Token next;
      bufferNext();
      next = bufferCurrentToken();
      
      // 演算子の重複チェック
      if (isOperator(next.tid)) {
        error = 1;
        puts("Multiple operators not allowed");
        break;
      }
      bufferBack();
      
      if (t.tid == multiply) {
        bufferNext();
        value *= fact();
      } else {
        bufferNext();
        double divisor = fact();
        if (divisor == 0) {
          error = 1;
          puts("Division by zero");
          break;
        }
        value /= divisor;
      }
    } else {
      bufferBack();
      break;
    }
  }
  stack_pop(value);
  return value;
}

double fact(void)
{
  stack_push("fact", bufferInd());

  double value = 0.0;
  Token t = bufferCurrentToken();

  if (t.tid == minus) {
    bufferNext();
    value = -fact();
  }
  else if (t.tid == left_parenthis) {
    bufferNext();
    value = expr();
    bufferNext();
    t = bufferCurrentToken();
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