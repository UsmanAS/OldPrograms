qsort: llist.o qsortlinked.o qsort.c
	gcc qsort.c llist.o qsortlinked.o -o qsort
msort: llist.o msortlinked.o msort.c
	gcc msort.c llist.o msortlinked.o -o msort
llist.o: list.h llist.c
	gcc -c llist.c
msortlinked.o: list.h msortlinked.c
	gcc -c msortlinked.c
qsortlinked.o: list.h llist.o qsortlinked.c
	gcc -c qsortlinked.c llist.o

