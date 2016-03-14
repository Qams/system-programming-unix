ex1open: defs.h t.o t.h
		gcc -Wall ex1open.c t.o -o ex1open
		echo Zbudowane

t.o: t.c t.h
		gcc -c -Wall t.c

clean:
		rm -f *~
		rm -f *.bak
		rm -f ex1open.o t.o

.PHONY: clean

