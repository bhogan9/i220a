CC = gcc
CPPFLAGS = -g -Wall -std=c11
LDFLAGS = -lm

C_FILES = $(wildcard *.c)

O_FILES = $(C_FILES:c=o)

TARGET = hamming-encode

all:		$(TARGET)

$(TARGET):	$(O_FILES)
		$(CC) $(O_FILES) $(LDFLAGS) -o $@
		$(MAKE) hamming-decode
		$(MAKE) clean

hamming-decode:	hamming-encode
		ln -s -f $< $@

.PHONY:		clean
clean:
		rm -rf *~ *.o
clean-all:
		rm hamming-encode hamming-decode
