PREFIX = $(HOME)/pattern
BINDIR = $(PREFIX)/bin
MANDIR = $(PREFIX)/man/man1

PROGRAM = sbfs_knn sffs_knn sbs_knn sfs_knn

MANDOC = sbfs_knn.1 sffs_knn.1 sbs_knn.1 sfs_knn.1

SCRIPT =

INCLUDE = -I../libs

CCFLAG = -Wall -O3 -g

LIBRARY = -L../libs

LDFLAG = -lpattern -lm

CC = gcc

base_OBJ = \
	k_nn_disc.o data_split.o set_split.o free_prm.o output.o shuffle.o \
	alloc_prm.o dist_sort.o fs_sort.o print_fs.o eval_best.o \
	read_data.o calc_dist.o find_class.o read_opt.o init_step.o \
	get_min_index.o

sbfs_knn_OBJ = \
	$(base_OBJ) add_one.o check.o remove_one.o sbs.o sbfs_knn.o

sffs_knn_OBJ = \
	$(base_OBJ) add_one.o check.o remove_one.o sfs.o sffs_knn.o

sbs_knn_OBJ = \
	$(base_OBJ) remove_one.o sbs.o sbs_knn.o

sfs_knn_OBJ = \
	$(base_OBJ) add_one.o sfs.o sfs_knn.o

all: $(PROGRAM)

sbfs_knn: $(sbfs_knn_OBJ) float_fs.h
	$(CC) $(CCFLAG) -o $@ $(sbfs_knn_OBJ) $(LIBRARY) $(LDFLAG)

sffs_knn: $(sffs_knn_OBJ) float_fs.h
	$(CC) $(CCFLAG) -o $@ $(sffs_knn_OBJ) $(LIBRARY) $(LDFLAG)

sbs_knn: $(sbs_knn_OBJ) float_fs.h
	$(CC) $(CCFLAG) -o $@ $(sbs_knn_OBJ) $(LIBRARY) $(LDFLAG)

sfs_knn: $(sfs_knn_OBJ) float_fs.h
	$(CC) $(CCFLAG) -o $@ $(sfs_knn_OBJ) $(LIBRARY) $(LDFLAG)

.c.o:
	$(CC) -c $< $(CCFLAG) $(INCLUDE)

clean:
	$(RM) $(PROGRAM) *.o *~

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
