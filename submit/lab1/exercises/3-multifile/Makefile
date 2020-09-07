PROJECT = key-value
SRC_FILES = main.c quadr.c quadr.h

CFLAGS = -g -Wall -std=c11
LDFLAGS = -ls
$(PROJECT):	quadr.o main.o
		$(CC) quadr.o main.o -o $(LDFLAGS) $@

clean:
		rm -f *.o $(PROJECT)
