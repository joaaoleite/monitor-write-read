all: escritor_par leitor_par monitor
	
escritor_par: escritor_par.c
	gcc -pthread -o escritor_par escritor_par.c 
leitor_par: leitor_par.c
	gcc -pthread -o leitor_par leitor_par.c
monitor: monitor.c
	gcc -g -pthread -o monitor monitor.c
run: monitor
	./monitor
