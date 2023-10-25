CC = gcc
CFLAGS = -Wall

all: p1.exe p2.exe p3.exe p4.exe

p1.exe: p1.c
	$(CC) $(CFLAGS) -o p1.exe p1.c

p2.exe: p2.c
	$(CC) $(CFLAGS) -o p2.exe p2.c

p3.exe: p3.c
	$(CC) $(CFLAGS) -o p3.exe p3.c

p4.exe: p4.c
	$(CC) $(CFLAGS) -o p4.exe p4.c

clean:
	rm -f p1.exe p2.exe p3.exe p4.exe

.PHONY: all clean
