all: dirinfo.c
	gcc -o program dirinfo.c

run:
	./program

clean:
	rm *.o
	rm program
