all: atendimento analista cliente
	@echo "compiled"
atendimento:
	clear
	gcc -o3 -lpthread -Wall -Wextra  atendimento.c -o atendimento.out
analista:
	gcc -o3 -lpthread analista.c -o analista.out
cliente:
	gcc cliente.c -o cliente.out
clean:
	rm -rf *.out
	clear