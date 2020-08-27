run: FFT.o S2DE.o
	gcc -Wall -o run FFT.o S2DE.o -lm -lglut -lGL -lX11
	rm -f *.o



#FFT (Fast Fourrier Transform)
FFT.o: FFT.c data.c S2DE.h
	gcc -Wall -O2 -c FFT.c



#S2DE management (use S2DE.o/.h to access to 2D graphic engine)
S2DE.o: S2DE.c S2DE.h
	gcc -Wall -O2 -c S2DE.c -I/usr/include/GL

