all:
	g++ -c -O4 main.c
	g++ -o main main.o

clean:
	rm -f *.o *~ main

install: all
	cp main /usr/local/bin/float-to-u8

uninstall: all
	rm -f main /usr/local/bin/float-to-u8
