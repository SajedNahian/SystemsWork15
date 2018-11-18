all: forkin.o
	gcc -o a.out forkin.o
forkin.o: forkin.c
	gcc -c forkin.c
clean:
	rm *.o
	rm a.out
run:
	./a.out