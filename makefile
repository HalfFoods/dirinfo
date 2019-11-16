all: dirinfo.o
	gcc -o program dirinfo.o

stat.o: dirinfo.c
	gcc -c dirinfo.c

run:
	./program

clean:
	rm *.o
	rm program
