all: escritor escritor_par leitor leitor_par
	
escritor: escritor.c
	gcc -o escritor escritor.c
escritor_par: escritor_par.c
	gcc -o escritor_par escritor_par.c 
leitor: leitor.c
	gcc -o leitor leitor.c
leitor_par: leitor_par.c
	gcc -o leitor_par leitor_par.c
run: escritor_par
	./escritor_par ; ./leitor_par
