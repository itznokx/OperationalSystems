all: main.o fatorial
	gcc main.c -o main
main.o:
	gcc main.c -c
clean:
	rm *.o
	clear
fatorial.o:
	gcc fatorial.c -c
fatorial: fatorial.o
	gcc fatorial.c -o fatorial