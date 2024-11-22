printer.o:
	gcc -c printer.c
printer: printer.o
	gcc printer.c -o printer
writer.o:
	gcc -c printer.c
writer: writer.o
	gcc writer.c -o writer 
compile: writer printer
	echo "compiled"
	make clean
all: compile
	./writer
clean:
	rm *.o
