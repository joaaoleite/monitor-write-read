#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "escritor.h"

int main(){

	int pid, status, i, duration;
	time_t inicio, fim;

	srand(time(NULL)); 		/* Inicializa funcao para medir o tempo */

	inicio = time(NULL); 	/* Regista o tempo inicial */

	for(i = 0; i < N_FORK; i++){

		pid = fork(); 			/* Cria processo filho */

		if(pid == -1){

			perror("Fork: Failed");
			exit(-1);
		}

		else if(pid == 0){

			execl("escritor", "escritor", 0);		/* Cada filho executa um escritor */
			exit(0);
		}
	}

	for(i = 0; i < N_FORK; i++)
		wait(&status);			/* Processo pai sincronizado com os 10 filhos */

	fim = time(NULL); 		/* Regista o tempo final */


	duration = fim - inicio; 		/* Calcula a diferenca de tempo */
	printf("O tempo decorrido foi %d segundos.\n", duration);

	return 0;
}
