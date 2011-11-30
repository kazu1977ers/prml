PROGRAM = libpattern.a

CC = gcc

INCLUDE = -I.

CCFLAG = -Wall -O3 -g

AR = ar cru

RANLIB = ranlib

libpattern_OBJS = \
	ary_utils.o calc_utils.o mat_utils.o opt_utils.o complex.o

all: $(PROGRAM)

install:

clean:

uninstall:

libpattern.a: $(libpattern_OBJS)
	$(AR) $(PROGRAM) $(libpattern_OBJS)
	$(RANLIB) $(PROGRAM)

ary_utils.c: ary_utils.h 

calc_utils.c: calc_utils.h

mat_utils.c: mat_utils.h

opt_utils.c: opt_utils.h

complex.c: complex.h

.c.o:
	$(CC) -c $< $(CCFLAG) $(INCLUDE)

clean:
	$(RM) $(libpattern_OBJS) $(PROGRAM) *~
