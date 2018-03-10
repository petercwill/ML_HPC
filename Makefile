# MKL needs module load intel/17.0.1
all: ./lab1  

lab1: lab1.o C1.o C4.o C5.o 
	gcc $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $(LDLIBS) C1.o C4.o C5.o lab1.o -o lab1

lab1.o : lab1.c C1.h C4.h C5.h
	gcc $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $(LDLIBS) -c lab1.c


C1.o : C1.c
	gcc $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $(LDLIBS) -c C1.c

C4.o : C4.c
	gcc $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $(LDLIBS) -c C4.c

C5.o : C5.c C4.h
	gcc $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $(LDLIBS) -c C5.c

clean:
	rm ./lab1


MKLDIR := /share/apps/intel/17.0.1/mkl
CPPFLAGS := -I$(MKLDIR)/include -D_GNU_SOURCE
CFLAGS := -O2 -W -Wall -std=c99

LDFLAGS := -L$(MKLDIR)/lib/intel64
LDLIBS := -lmkl_intel_lp64 -lmkl_sequential -lmkl_core -lm

.PHONY: clean

