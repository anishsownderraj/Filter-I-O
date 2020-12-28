CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic -std=c99


all: hatterspeak

hatterspeak: hatterspeak.o bv.o speck.o hs.o bf.o ll.o hash.o parser.o
	$(CC) -o hatterspeak hatterspeak.o bv.o speck.o hs.o bf.o ll.o hash.o parser.o -lm

hatterspeak.o: hatterspeak.c bv.h speck.h hs.h bf.h ll.h hash.h parser.h 
	$(CC) $(CFLAGS) -c hatterspeak.c

bv.o: bv.c bv.h
	$(CC) $(CFLAGS) -c bv.c

speck.o: speck.c speck.h
	$(CC) $(CFLAGS) -c speck.c

hs.o: hs.c hs.h
	$(CC) $(CFLAGS) -c hs.c

bf.o: bf.c bf.h 
	$(CC) $(CFLAGS) -c bf.c 

ll.o: ll.c ll.h
	$(CC) $(CFLAGS) -c ll.c

hash.o: hash.c hash.h
	$(CC) $(CFLAGS) -c hash.c

parser.o: parser.c parser.h
	$(CC) $(CFLAGS) -c parser.c


clean:
	rm -rf hatterspeak hatterspeak.o bv.o ll.o speck.o hs.o bf.o ll.o hash.o parser.o infer-out

infer:
	make clean; infer-capture -- make; infer-analyze -- make

valgrind:
	valgrind ./hatterspeak
