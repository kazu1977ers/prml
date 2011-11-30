PREFIX = $(HOME)/pattern

BINDIR = $(PREFIX)/bin

MANDIR = $(PREFIX)/man/man1

PROGRAM = \
	addmat contour delmat detect_fi file_split gamma_val gencomb \
	histo invmat meancov minmax multmat normalize norm_val \
	npow nqrt rank_fi round_off shuffle subtr_ap transmat vecarg eigen \
	corrmat

SCRIPT = 	\
	add_class cinfo_reader delete_class dinfo_reader gen_cri_fig \
	gen_rate_table rotate_fig trace_fi get_opt syori_to_c45 \
	syori_to_svm gen_rate_fs_fig getrpth

MANDOC_PROG = \
	addmat.1 contour.1 delmat.1 detect_fi.1 file_split.1 gamma_val.1 \
	gencomb.1 histo.1 invmat.1 meancov.1 minmax.1 multmat.1 norm_val.1 \
	normalize.1 npow.1 nqrt.1 rank_fi.1 shuffle.1 subtr_ap.1 \
	transmat.1 round_off.1 vecarg.1 eigen.1 corrmat.1

MANDOC_SCRPT	= \
	add_class.1 cinfo_reader.1 delete_class.1 dinfo_reader.1 \
	gen_cri_fig.1 gen_rate_table.1 rotate_fig.1 trace_fi.1 \
	get_opt.1 syori_to_c45.1 syori_to_svm.1 gen_rate_fs_fig.1 \
	getrpth.1

MANDOC = $(MANDOC_PROG) $(MANDOC_SCRPT)

INCLUDE = -I../libs

CCFLAG = -Wall -O3 -g

LIBRARY = -L../libs

LDFLAG = -lpattern -lm

CC = gcc

addmat_OBJ = addmat.o
corrmat_OBJ = corrmat.o
contour_OBJ = contour.o
delmat_OBJ = delmat.o
gamma_val_OBJ = gamma_val.o
gencomb_OBJ = gencomb.o
histo_OBJ = histo.o
invmat_OBJ = invmat.o
meancov_OBJ = meancov.o
minmax_OBJ = minmax.o
multmat_OBJ = multmat.o
norm_val_OBJ = norm_val.o
normalize_OBJ = normalize.o
npow_OBJ = npow.o
nqrt_OBJ = nqrt.o
transmat_OBJ = transmat.o
file_split_OBJ = file_split.o
shuffle_OBJ = shuffle.o
rank_fi_OBJ = rank_fi.o
subtr_ap_OBJ = subtr_ap.o
detect_fi_OBJ = detect_fi.o
round_off_OBJ = round_off.o
vecarg_OBJ = vecarg.o
eigen_OBJ = eigen.o

all: $(PROGRAM)

addmat: $(addmat_OBJ)
	$(CC) $(CCFLAG) -o $@ $(addmat_OBJ) $(LIBRARY) $(LDFLAG)

corrmat: $(corrmat_OBJ)
	$(CC) $(CCFLAG) -o $@ $(corrmat_OBJ) $(LIBRARY) $(LDFLAG)

contour: $(contour_OBJ)
	$(CC) $(CCFLAG) -o $@ $(contour_OBJ) $(LIBRARY) $(LDFLAG)

delmat: $(delmat_OBJ)
	$(CC) $(CCFLAG) -o $@ $(delmat_OBJ) $(LIBRARY) $(LDFLAG)

gamma_val: $(gamma_val_OBJ)
	$(CC) $(CCFLAG) -o $@ $(gamma_val_OBJ) $(LIBRARY) $(LDFLAG)

gencomb: $(gencomb_OBJ)
	$(CC) $(CCFLAG) -o $@ $(gencomb_OBJ) $(LIBRARY) $(LDFLAG)

histo: $(histo_OBJ)
	$(CC) $(CCFLAG) -o $@ $(histo_OBJ) $(LIBRARY) $(LDFLAG)

invmat: $(invmat_OBJ)
	$(CC) $(CCFLAG) -o $@ $(invmat_OBJ) $(LIBRARY) $(LDFLAG)

meancov: $(meancov_OBJ)
	$(CC) $(CCFLAG) -o $@ $(meancov_OBJ) $(LIBRARY) $(LDFLAG)

minmax: $(minmax_OBJ)
	$(CC) $(CCFLAG) -o $@ $(minmax_OBJ) $(LIBRARY) $(LDFLAG)

multmat: $(multmat_OBJ)
	$(CC) $(CCFLAG) -o $@ $(multmat_OBJ) $(LIBRARY) $(LDFLAG)

norm_val: $(norm_val_OBJ)
	$(CC) $(CCFLAG) -o $@ $(norm_val_OBJ) $(LIBRARY) $(LDFLAG)

normalize: $(normalize_OBJ)
	$(CC) $(CCFLAG) -o $@ $(normalize_OBJ) $(LIBRARY) $(LDFLAG)

npow: $(npow_OBJ)
	$(CC) $(CCFLAG) -o $@ $(npow_OBJ) $(LIBRARY) $(LDFLAG)

nqrt: $(nqrt_OBJ)
	$(CC) $(CCFLAG) -o $@ $(nqrt_OBJ) $(LIBRARY) $(LDFLAG)

transmat: $(transmat_OBJ)
	$(CC) $(CCFLAG) -o $@ $(transmat_OBJ) $(LIBRARY) $(LDFLAG)

file_split: $(file_split_OBJ)
	$(CC) $(CCFLAG) -o $@ $(file_split_OBJ) $(LIBRARY) $(LDFLAG)

shuffle: $(shuffle_OBJ)
	$(CC) $(CCFLAG) -o $@ $(shuffle_OBJ) $(LIBRARY) $(LDFLAG)

rank_fi: $(rank_fi_OBJ)
	$(CC) $(CCFLAG) -o $@ $(rank_fi_OBJ) $(LIBRARY) $(LDFLAG)

subtr_ap: $(subtr_ap_OBJ)
	$(CC) $(CCFLAG) -o $@ $(subtr_ap_OBJ) $(LIBRARY) $(LDFLAG)

detect_fi: $(detect_fi_OBJ)
	$(CC) $(CCFLAG) -o $@ $(detect_fi_OBJ) $(LIBRARY) $(LDFLAG)

round_off: $(round_off_OBJ)
	$(CC) $(CCFLAG) -o $@ $(round_off_OBJ) $(LIBRARY) $(LDFLAG)

vecarg: $(vecarg_OBJ)
	$(CC) $(CCFLAG) -o $@ $(vecarg_OBJ) $(LIBRARY) $(LDFLAG)

eigen: $(eigen_OBJ)
	$(CC) $(CCFLAG) -o $@ $(eigen_OBJ) $(LIBRARY) $(LDFLAG)

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
