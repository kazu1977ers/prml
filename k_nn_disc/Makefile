PREFIX = $(HOME)/pattern

BINDIR = $(PREFIX)/bin

MANDIR = $(PREFIX)/man/man1

PROGRAM = k_nn_disc

MANDOC	= k_nn_disc.1

SCRIPT = 

INCLUDE = -I../libs

CCFLAG = -Wall -O3 -g

LIBRARY = -L../libs

LDFLAG = -lpattern -lm

CC = gcc

k_nn_disc_OBJ = \
	alloc_param.o calc_dist.o disc.o free_param.o \
	init_param.o output.o quick_sort.o read_data.o read_opt.o \
	k_nn_disc.o

all: $(PROGRAM)

k_nn_disc: $(k_nn_disc_OBJ) k_nn_disc.h
	$(CC) $(CCFLAG) -o $@ $(k_nn_disc_OBJ) $(LIBRARY) $(LDFLAG)

.c.o:
	$(CC) -c $< $(CCFLAG) $(INCLUDE)

clean:
	$(RM) $(PROGRAM) *~ *.o

install: $(PROGRAM) $(MANDOC) $(SCRIPT)
	test -z "$(BINDIR)" || mkdir -p -- "$(BINDIR)"
	test -z "$(MANDIR)" || mkdir -p -- "$(MANDIR)"
	for p in $(PROGRAM); \
	do \
		install -c -s -m 755 "$$p" "$(BINDIR)"; \
	done
	for p in $(MANDOC); \
	do \
		install -c -m 644 "$$p" "$(MANDIR)"; \
	done
	for p in $(SCRIPT); \
	do \
		install -c -m 755 "$$p" "$(BINDIR)"; \
	done

uninstall:
	for p in $(PROGRAM); \
	do \
		$(RM) "$(BINDIR)/$$p"; \
	done
	for p in $(MANDOC); \
	do \
		$(RM) "$(MANDIR)/$$p"; \
	done
	for p in $(SCRIPT); \
	do \
		$(RM) "$(BINDIR)/$$p"; \
	done
