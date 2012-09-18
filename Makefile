modracfucker: main.c main.o
	gcc -g -c main.c
	gcc -g -o modracfucker main.o -lssh

clean:
	rm main.c main.o
