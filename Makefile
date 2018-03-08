all: ./lab1  

lab1: C1.o
	gcc -o lab1 C1.o

C1.o : C1.c gcc -c C1.c 
clean:
	rm ./lab1

# MKL needs module load intel/17.0.1
MKLDIR := /share/apps/intel/17.0.1/mkl
CPPFLAGS := -I$(MKLDIR)/include -D_GNU_SOURCE
CFLAGS := -O2 -W -Wall -std=c99

LDFLAGS := -L$(MKLDIR)/lib/intel64
LDLIBS := -lmkl_intel_lp64 -lmkl_sequential -lmkl_core -lm

.PHONY: clean
