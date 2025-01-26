CC　= cc
CFLAGS = -I/usr/local/include
EXENAME = parse_test
OBJS = parse_test.o parse_infix.o lex_infix.o stack_tracer.o
SOURCES = parse_test.c parse_infix.c lex_infix.c stack_tracer.c
TESTSOURCES = test1_lex_infix.c test2_lex_infix.c
INCLUDES = parse_infix.h lex_infix.h stack_tracer.h
MAKEFILE = makefile
ZIPFILE = parse_infix.zip

# Main target 
$(EXENAME): $(OBJS)
	$(CC) -o $(EXENAME) $(OBJS)

# test program for parse_lex
test1: test1_lex_infix.o lex_infix.o
	$(CC) -o test1 test1_lex_infix.o lex_infix.o

test2: test2_lex_infix.o lex_infix.o
	$(CC) -o test2 test2_lex_infix.o lex_infix.o

.SUFFIXES: .c .o
.c.o:
	$(CC) -c $(CFLAGS) $<

# include dependencies
parse_infix.o lex_infix.o: lex_infix.h
parse_infix.o stack_tracer.o: stack_tracer.h
parse_test.o: parse_infix.h
test1_lex_infix.o test2_lex_infix.o: lex_infix.h

# utilities
clear:
	rm *.o *~ *.zip *.gch test1 test2 parse_test 2>/dev/null

# for zipping parse_infix modules
ZIP:
	zip $(ZIPFILE) $(SOURCES) $(INCLUDES) $(MAKEFILE)

# with test sources
ZIPALL:
	zip $(ZIPFILE) $(SOURCES) $(INCLUDES) $(TESTSOURCES) $(MAKEFILE)
