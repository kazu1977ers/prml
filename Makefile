PREFIX = $(HOME)/github/prml

SUBDIR = \
	libs \
	k_nn_disc \
	csfs_knn \
	utils

all:
	for p in $(SUBDIR); \
	do \
		cd "$$p"; \
		make all PREFIX=$(PREFIX); \
		cd ..; \
	done

clean:
	for p in $(SUBDIR); \
	do \
		cd "$$p"; \
		make clean PREFIX=$(PREFIX); \
		cd ..; \
	done

install:
	for p in $(SUBDIR); \
	do \
		cd "$$p"; \
		make install PREFIX=$(PREFIX); \
		cd ..; \
	done

uninstall:
	for p in $(SUBDIR); \
	do \
		cd "$$p"; \
		make uninstall PREFIX=$(PREFIX); \
		cd ..; \
	done
