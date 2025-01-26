#include <stdio.h>

enum TokenID { plus, minus, multiply, substitute, left_parenthis,
  right_parenthis, number, eos, other};

typedef struct { enum TokenID tid; double value;}  Token;
// tid: token ID
// value: the numerical value when tid=number

typedef struct { char sexpr[BUFSIZ]; int ind; int previous; } Buffer;
// sexpr: string buffer for the target expression
// ind: pointer that indicates the current position on sexp

// public functions
extern void bufferInit(char* targetString);
extern void bufferNext(void);
extern void bufferBack(void);
extern Token bufferCurrentToken(void);
extern int bufferInd(void); // for debug
