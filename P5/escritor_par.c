#include "readwriter.h"

int finish = 0, mutex_enable = 1, error_enable = 0;
char *cadeia[10] = {"aaaaaaaaa\n","bbbbbbbbb\n","ccccccccc\n","ddddddddd\n","eeeeeeeee\n",
				    "fffffffff\n","ggggggggg\n","hhhhhhhhh\n","iiiiiiiii\n","jjjjjjjjj\n"};

pthread_mutex_t vec_mutex[N_FILES];

void usr1_handler(){
	mutex_enable++;
	puts("Received mutex toogle!");
}

void usr2_handler(){
	error_enable++;
	puts("Received error toogle!");
}

void stop_handler(){
	finish = 1;
	puts("Writer received stop!");
}

int escritor(){

	int file, escolhida, id_file, k, local_enable;
	char filename[13];

	while(1){

		local_enable = mutex_enable;

		if(finish) return 0;

		strcpy(filename, "SO2014-0.txt");

		id_file = rand() % N_FILES;
		filename[INDICE_ID_FILE] += id_file;

  		file = open(filename, O_RDWR | O_CREAT, PERMISSION_CODE_W);

		if (file < 0){
			perror("Open: Failed\n");
			return -1;
		}

		if(local_enable % 2){
			if(flock(file, LOCK_EX) < 0){
				perror("Flock on Lock: Failed.\n");
				close(file);
				return -1;
			}
		}

		if(pthread_mutex_lock(&vec_mutex[id_file]) != 0){
  			perror("Lock mutex: Failed");
  			flock(file, LOCK_UN);
  			close(file);
  			return -1;
  		}

		escolhida = rand() % 10; /*Linha de caracteres aleatoria*/

  		if(error_enable % 2) write(file, "zzzzzzzzz\n", 10);
  		else write(file, cadeia[escolhida], 10);

		for(k = 1; k < N_LINES; k++){

			if(write(file, cadeia[escolhida], 10) != 10){ /*Se nao escrever 10 caracteres da erro*/
		        perror("Write line: Failed\n");
		        pthread_mutex_unlock(&vec_mutex[id_file]);
		        flock(file, LOCK_UN);
				close(file);
				return -1;
			}
		}

		if(pthread_mutex_unlock(&vec_mutex[id_file]) != 0){
  			perror("Unlock mutex: Failed");
  			flock(file, LOCK_UN);
  			close(file);
  			return -1;
  		}

  		if(local_enable % 2){
			if(flock(file, LOCK_UN) < 0){
				perror("Flock on Lock: Failed.\n");
				close(file);
				return -1;
			}
		}

		close(file);
	}

	return 0;
}

int main(){

	int i, j;
	pthread_t thread_array[N_THREAD_WRITE];

	struct sigaction new_action1;
	struct sigaction new_action2;
	struct sigaction new_action3;	

  	new_action1.sa_handler = usr1_handler;
  	sigemptyset (&new_action1.sa_mask);
  	sigaddset(&new_action1.sa_mask, SIGUSR1);
  	new_action1.sa_flags = 0;
  	sigaction(SIGUSR1, &new_action1, NULL);

  	new_action2.sa_handler = usr2_handler;
  	sigemptyset (&new_action2.sa_mask);
  	sigaddset(&new_action2.sa_mask, SIGUSR2);
  	new_action2.sa_flags = 0;
  	sigaction(SIGUSR2, &new_action2, NULL);

  	new_action3.sa_handler = stop_handler;
  	sigemptyset (&new_action3.sa_mask);
  	sigaddset(&new_action3.sa_mask, SIGTSTP);
  	new_action3.sa_flags = 0;
  	sigaction(SIGTSTP, &new_action3, NULL);

	srand(time(NULL));

	for(i = 0; i < N_FILES; i++){

		if(pthread_mutex_init(&vec_mutex[i], NULL) != 0){
			perror("Initialize mutex: Failed");
			return -1;
		}
	}

	for(i = 0; i < N_THREAD_WRITE; i++){

	  	if(pthread_create(&thread_array[i], NULL, (void *) escritor, NULL) != 0){
	  		perror("Create thread: Failed");
			return -1;
		}

	}
	
  	for(i = 0; i < N_THREAD_WRITE; i++){

		if(pthread_join(thread_array[i], NULL) != 0){
			perror("Join thread: Failed");
			return -1;
		}
	}

	return 0;
}
