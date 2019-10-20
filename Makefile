
OUTPATH         = bin

all:
	cd double-to-u8   && make && cd ..
	cd float-to-u8    && make && cd ..
	cd u8-to-double   && make && cd ..
	cd u8-to-float    && make && cd ..

install:
	cd double-to-u8   && make install && cd ..
	cd float-to-u8    && make install && cd ..
	cd u8-to-double   && make install && cd ..
	cd u8-to-float    && make install && cd ..

clean:
	cd double-to-u8   && make clean && cd ..
	cd float-to-u8    && make clean && cd ..
	cd u8-to-double   && make clean && cd ..
	cd u8-to-float    && make clean && cd ..
