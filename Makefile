# File IO ++
# "fileiopp"
# M. Yamanaka
# email: myamanaka@live.com
# website: http://www.csmyamanaka.com
# license: MIT (See included "LICENSE" file for details)

FILES=varbyterw.c bmpfileiopp.c
OBJS=varbyterw.o bmpfileiopp.o
TESTER=tester.c
CC=gcc
LK=ld
SOFILE=libfileiopp.so
OFILE=fileiopp.o
OUT=Tester

tester: tester.c fileiopp.o
	$(CC) -o $(OUT) $^

sofile: $(OBJS)
	$(CC) -o $(SOFILE) -shared $(OBJS)
	rm $(OBJS)

fileiopp.o: $(OBJS)
	$(LK) -o $(OFILE) -i $(OBJS)
	rm $(OBJS)

objects: $(FILES)
	$(CC) -c $(FILES)

clean:
	rm -f *.o *.so *.a *.out $(OUT) example*
