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


int bufferCurrentTokenLength(void);

// -- public functions --

void bufferInit(char* string)
{
  strcpy(buf.sexpr, string);
  buf.ind = 0;
  buf.previous = 0;
}

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
  else if (buf.sexpr[index] == '.') {
    t.tid = other;  // 先頭の小数点はエラー
  }
  else if (isdigit(buf.sexpr[index])) {
    t.tid = number;
    
    // 先頭が0で次が数字の場合はエラー
    if (buf.sexpr[index] == '0' && isdigit(buf.sexpr[index + 1])) {
      t.tid = other;
      return t;
    }
    
    // 整数部分の処理
    while (isdigit(buf.sexpr[index])) {
      t.value = t.value * 10 + (double)(buf.sexpr[index] - '0');
      index++;
    }
    
    // 小数点と小数部分の処理
    if (buf.sexpr[index] == '.') {
      index++;
      // 小数点の後に数字がない場合はエラー
      if (!isdigit(buf.sexpr[index])) {
        t.tid = other;
        return t;
      }
      double decimal_place = 0.1;
      while (isdigit(buf.sexpr[index])) {
        t.value = t.value + (double)(buf.sexpr[index] - '0') * decimal_place;
        decimal_place *= 0.1;
        index++;
      }
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
    if (buf.sexpr[index] == '.') {
      index++;
      while (isdigit(buf.sexpr[index])) {
        index++;
      }
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