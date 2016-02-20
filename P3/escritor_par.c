#include "readwriter.h"

int main(){

	int i, pid, status;

	struct timeval tvstart, tvend, tvduration;
  	unsigned int duration;

  	gettimeofday(&tvstart, NULL);

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

	gettimeofday(&tvend, NULL);

	tvduration.tv_sec = tvend.tv_sec - tvstart.tv_sec;
	tvduration.tv_usec = tvend.tv_usec - tvstart.tv_usec;
	duration = tvduration.tv_sec * 1000000 + tvduration.tv_usec;
	printf("O tempo de execucao foi %d microssegundos.\n", duration);

  return 0;
}
