all: escritor escritor_par leitor
	
escritor: escritor.c
	gcc -o escritor escritor.c
escritor_par: escritor_par.c
	gcc -o escritor_par escritor_par.c 
leitor: leitor.c
	gcc -o leitor leitor.c
run: escritor_par
	./escritor_par ; ./leitor
