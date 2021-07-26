main2: main2.o libisentlib.a
	gcc -Wall main2.o -o main2 libisentlib.a -lm -lglut -lGL -lX11
main2.o: main2.c GfxLib.h BmpLib.h ESLib.h
	gcc -Wall -c main2.c -I/usr/include/GL

libisentlib.a: BmpLib.o ErreurLib.o ESLib.o GfxLib.o OutilsLib.o SocketLib.o ThreadLib.o TortueLib.o VectorLib.o WavLib.o fctsprite.o fctsauvegarde.o
	ar r libisentlib.a BmpLib.o ErreurLib.o ESLib.o GfxLib.o OutilsLib.o SocketLib.o ThreadLib.o TortueLib.o VectorLib.o WavLib.o fctsprite.o fctsauvegarde.o
	ranlib libisentlib.a

BmpLib.o: BmpLib.c BmpLib.h OutilsLib.h
	gcc -Wall -O2 -c BmpLib.c

ESLib.o: ESLib.c ESLib.h ErreurLib.h
	gcc -Wall -O2 -c ESLib.c

GfxLib.o: GfxLib.c GfxLib.h ESLib.h
	gcc -Wall -O2 -c GfxLib.c -I/usr/include/GL
	
OutilsLib.o: OutilsLib.c OutilsLib.h
	gcc -Wall -O2 -c OutilsLib.c
	
ErreurLib.o: ErreurLib.c ErreurLib.h
	gcc -Wall -O2 -c ErreurLib.c

fctsprite.o: fctsprite.c fctsprite.h
	gcc -Wall -O2 -c fctsprite.c
fctsauvegarde.o: fctsauvegarde.c fctsauvegarde.h
	gcc -Wall -O2 -c fctsauvegarde.c	
SocketLib.o: SocketLib.c SocketLib.h
	gcc -Wall -O2 -c SocketLib.c
	
ThreadLib.o: ThreadLib.c ThreadLib.h
	gcc -Wall -O2 -c ThreadLib.c
	
WavLib.o: WavLib.c WavLib.h OutilsLib.h
	gcc -Wall -O2 -c WavLib.c -Wno-unused-result

zip:
	tar -cvzf libisentlib.tgz *.[ch] *.bmp *.pdf makefile

clean:
	rm -f *~ *.o

deepclean: clean
	rm -f main2 libisentlib.a
	rm -f main
