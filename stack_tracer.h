// ---- Stack tracer ----
// stack_push to be called at the entry point of the parse function_name
// stack_pos to be called at the exit pont of the parse function
// These functions respectively print function name and retern value
// with # of tabs corresponding to the the stacke level

extern int trace_mode;  // default 0, if 0, do nothing.
extern void stack_push(char* function_name, int ind/*buffer pointer*/);
extern void stack_pop(double return_value);
