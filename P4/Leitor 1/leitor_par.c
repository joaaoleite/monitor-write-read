#include "readwriter.h"

int escolher_ficheiro(){ /*Escolhe ficheiro entre 5, aleatoriamente*/

	int id_file = rand() % 5;
	
	return id_file;
}

int main(){

	int i, pid, status, valorExit;
	char buffer[2];

  	for(i = 0; i < N_FORK_READ; i++){

		pid = fork(); 			/* Cria processo filho */

		if(pid == -1){

			perror("Fork: Failed");
			exit(-1);
		}

		else if(pid == 0){

			srand(time(NULL) ^ ((getpid() * 8) << 16));

			sprintf(buffer, "%d", escolher_ficheiro());

			execl("leitor", "leitor", buffer, NULL);
			exit(-1);
		}
	}

	for(i = 0; i < N_FORK_READ; i++){

		if(wait(&status) == -1)
			perror("Leitor: Failed.");

		else if(WIFEXITED(status)){
  			valorExit = (char) WEXITSTATUS(status);
  			printf("Filho terminou e devolveu %d\n", valorExit);
		}

		else
			perror("Nao acabou com exit/return.");
	}

  return 0;
}