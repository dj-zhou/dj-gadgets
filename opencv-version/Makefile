LIBS+=-lopencv_core

all:
	g++ -c -O4 src/main.cpp
	g++ -o main main.o  $(LIBS)

clean:
	rm -f *.o *~ main

install: all
	cp main /usr/local/bin/opencv-version
