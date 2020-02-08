all:
	gcc -c -O4 main.c
	gcc -c -O4 funcs.c
	gcc -c -O4 file-create.c
	gcc -c -O4 time-fetch.c
	gcc -c -O4 prompt-msg.c
	gcc -o djfile main.o funcs.o file-create.o time-fetch.o prompt-msg.o
clean:
	rm -f *.o *~ djfile
