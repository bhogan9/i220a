PROJECT = quadr
SRC_FILES = main.c quadr.c quadr.h

CFLAGS = -g -Wall -std=c11
LDFLAGS = -lm

dist:
	$(PROJECT).tar.gz

$(PROJECT).tar.gz:	$(SRC_FILES)
			tar -cf $(PROJECT).tar $(SRC_FILES)
			gzip -f $(PROJECT).tar

$(PROJECT):	quadr.o main.o
		$(CC) quadr.o main.o -o $(LDFLAGS) $@

depend:
	$(CC) -MM $(CPPFLAGS) *.c

clean:
		rm -f *.o $(PROJECT) $(PROJECT).tar.gz
