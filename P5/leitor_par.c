#include "readwriter.h"

pthread_mutex_t mutex;
sem_t semaphore[2];
char buffer[N_BUFFER][13], temp[13];
int ptr_read = 0, finish = 0;

int escolher_ficheiro(){ /*Escolhe ficheiro entre 5, aleatoriamente*/

	int id_file = rand() % 5;
	
	return id_file;
}

int leitor(){

	int file, i, wrong, x;
	char linha[10], primeira[10], filename[13];

	while(1){

		wrong = 0;
		i = 0;

		if(finish) break;

		if(sem_wait(&semaphore[0]) != 0){
			perror("Wait on semaphore0: Failed");
			return -1;
		}

		if(finish) break;

		if(pthread_mutex_lock(&mutex) != 0){
  			perror("Lock mutex: Failed");
  			return -1;
  		}

  		strcpy(filename, buffer[ptr_read]);

  		if(strcmp(filename, "") == 0){
  			pthread_mutex_unlock(&mutex);
  			continue;
  		}

  		ptr_read = (ptr_read + 1) % N_BUFFER;
  		
  		if(pthread_mutex_unlock(&mutex) != 0){
  			perror("Unlock mutex: Failed");
  			return -1;
  		}

  		if(sem_post(&semaphore[1]) != 0){
  			perror("Post semaphore1: Failed");
  			return -1;
  		}

		file = open(filename, O_RDONLY | PERMISSION_CODE_R);
		
		if (file < 0){
			perror("Open: Failed.\n");
			continue;
		}

		if(flock(file, LOCK_SH) < 0){
			perror("Flock on Lock: Failed.\n");
			close(file);
			return -1;
		}

		x = read(file, primeira, 10);
		printf("%d\n", x);

		if(x < 10){	/*Le a primeira linha para comparacao*/
			perror("First Read: Failed.\n");
			flock(file, LOCK_UN);
			close(file);
			continue;
		} 

		while(read(file, linha, 10) != 0){ /*Enquanto houver linhas no ficheiro*/

			if(strncmp(primeira, linha, 10) != 0){
				perror("Linha nao corresponde: Erro.\n");	/*Se linha diferente da primeira da erro*/
				wrong = 1;
			}

			if(wrong) break;

			i++;
		}

		if(flock(file, LOCK_UN) < 0){
			perror("Flock on Unlock: Failed.\n");
			close(file);
			return -1;
		}

		

		close(file);

		if(wrong) continue;

		if(i != (N_LINES - 1)){ /*Se acabou o ficheiro, sucesso*/
			perror("Não acabou o ficheiro: Erro.\n");
			return -1;
		}

		printf("Read success on %s!\n", filename);
	}

	return 0;
}

int main(){

	int i, receive;
	pthread_t thread_array[N_THREAD_READ];
	int ptr_write = 0;

	srand(time(NULL));

	if(pthread_mutex_init(&mutex, NULL) != 0){
		perror("Initialize mutex: Failed");
		return -1;
	}

	for(i = 0; i < 2; i++){

		if(sem_init(&semaphore[i], 0, i * N_BUFFER) != 0){
			perror("Initialize semaphore: Failed");
			return -1;
		}
	}

	for(i = 0; i < N_THREAD_READ; i++){

  		if(pthread_create(&thread_array[i], NULL, (void *) leitor, NULL) != 0){
  			perror("Create thread: Failed");
  			return -1;
  		}
  	}

  	while(1){

  		if(sem_wait(&semaphore[1]) != 0){
  			perror("Wait semaphore1: Failed");
  			return -1;
  		}

  		receive = read(0, temp, N_INPUT);

  		if(receive < 0){
  			perror("Read stream: Failed!\n");
  			continue;
  		}

  		else if(receive == 0){
  			finish = 1;
  			for(i = 0; i < N_THREAD_READ; i++)
  				sem_post(&semaphore[0]);
  			break;
  		}

  		strcpy(buffer[ptr_write], temp);

		ptr_write = (ptr_write + 1) % N_BUFFER;

  		if(sem_post(&semaphore[0]) != 0){
  			perror("Post semaphore0: Failed");
  			return -1;
  		}
  	}

  	puts("Reader finished");

  	for(i = 0; i < N_THREAD_READ; i++){

  		if(pthread_join(thread_array[i], NULL) != 0){
  			perror("Join thread: Failed");
  		}
  	}

  return 0;
}
