
OUTPATH         = bin

all:
	cd ascii-code   && make && cd ..
	cd double-to-u8 && make && cd ..
	cd float-to-u8  && make && cd ..
	cd u8-to-double && make && cd ..
	cd u8-to-float  && make && cd ..

install:
	cd ascii-code   && make install && cd ..
	cd double-to-u8 && make install && cd ..
	cd float-to-u8  && make install && cd ..
	cd u8-to-double && make install && cd ..
	cd u8-to-float  && make install && cd ..

clean:
	cd ascii-code   && make clean && cd ..
	cd double-to-u8 && make clean && cd ..
	cd float-to-u8  && make clean && cd ..
	cd u8-to-double && make clean && cd ..
	cd u8-to-float  && make clean && cd ..
