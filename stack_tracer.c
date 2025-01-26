#include <stdio.h>
#include "stack_tracer.h"

// ---- Stack tracer ----
int level = 0;
int trace_mode = 0;

// ---- public functions ----
void stack_push(char* func, int ind)
{
    if (trace_mode == 1) {
      int i;
      for (i = 0; i < level; i++) printf("\t");
      printf("%s(ind=%d)\n", func, ind);
      level++;
    }
}
void stack_pop(double value)
{
  if (trace_mode == 1) {
    int i;
    level--;
    for (i = 0; i < level; i++) printf("\t");
    printf("%f <-\n", value);
  }
}
