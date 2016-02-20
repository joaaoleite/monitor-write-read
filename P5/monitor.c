#include "readwriter.h"

int main(){

	int pid_w, pid_r, len, i, finish = 0, status;
	int fds[2];
	char input_buffer[100], *send;

	send = (char *) malloc(sizeof(char) * N_INPUT);

	pid_w = fork();

	if(pid_w < 0){
		perror("Fork Write: Failed!");
		return -1;
	}

	else if(pid_w == 0){
		execl("escritor_par", "escritor_par", NULL);
		perror("Exec Write: Failed!");
		exit(-1);
	}

	if(pipe(fds)){
		perror("Create pipe: Failed!\n");
		return -1;
	}

	pid_r = fork();

	if(pid_r < 0){
		perror("Fork Read: Failed!");
		return -1;
	}

	else if(pid_r == 0){
		close(0);
		dup(fds[0]);
		close(fds[0]);
		close(fds[1]);
		execl("leitor_par", "leitor_par", NULL);
		perror("Exec Read: Failed!");
		exit(-1);
	}

	else{

		close(fds[0]);
		
		while(1){
			memset(input_buffer, 0, N_INPUT);

			if(finish) break;

			read(0, input_buffer, N_INPUT - 1);

			send = strtok(input_buffer, " \n");
			
			while(send != NULL){

				if(strncmp(send, "sair", 4) == 0){
					kill(pid_w, SIGTSTP);
					close(fds[1]);
					finish = 1;
					break;
				}

				else if(strncmp(send, "il", 2) == 0){
					puts("Matar 1");
					kill(pid_w, SIGUSR1);
				}

				else if(strncmp(send, "ie", 2) == 0){
					puts("Matar 2");
					kill(pid_w, SIGUSR2);
				}

				else if(write(fds[1], send, N_INPUT) < 0){
					perror("Error to send!\n");
				}

				send = strtok(NULL, " \n");
			}
		}

		for(i = 0; i < 2; i++){
			wait(&status);
		}
	}
	return 0;
}