CC=g++
CFLAGS=-Wall -w

all: lcs floyd

lcs: lcs.cpp
	$(CC) $(CFLAGS) -o $@ $<

floyd: floyd.cpp
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f lcs floyd output.txt