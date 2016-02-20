#include "readwriter.h"

char *cadeia[10] = {"aaaaaaaaa\n","bbbbbbbbb\n","ccccccccc\n","ddddddddd\n","eeeeeeeee\n",
				    "fffffffff\n","ggggggggg\n","hhhhhhhhh\n","iiiiiiiii\n","jjjjjjjjj\n"};

long escolher_ficheiro(){ /*Escolhe ficheiro entre 5, aleatoriamente*/

	long id_file = rand() % 5;
	
	return id_file;
}

int leitor(void *arg){

	int file, i = 0;
	long res;
	char linha[10], primeira[10], filename[] = "SO2014-0.txt";

	filename[INDICE_ID_FILE] += ((int) arg);

	file = open(filename, O_RDWR | O_CREAT, PERMISSION_CODE);
	
	if (file < 0){
		perror("Open: Failed.\n");
		return -1;
	}

	if(read(file, primeira, 10) < 10){	/*Le a primeira linha para comparacao*/
		perror("First Read: Failed.\n");
		close(file);
		return -1;
	} 

	while(read(file, linha, 10) != 0){ /*Enquanto houver linhas no ficheiro*/

		if(strncmp(primeira, linha, 10) != 0){
			perror("Linha nao corresponde: Erro.\n");	/*Se linha diferente da primeira da erro*/
			close(file);
			return -1;
		}

		i++;
	}

	close(file);

	if(i != (N_LINES - 1)){ /*Se acabou o ficheiro, sucesso*/
		perror("Não acabou o ficheiro: Erro.\n");
		return -1;
	}
	return 0;
}

int main(){

	int i, x, threadReturn[N_THREAD_READ];
	pthread_t thread_array[N_THREAD_READ];

	srand(time(NULL));

  	for(i = 0; i < N_THREAD_READ; i++){

  		if((pthread_create(&thread_array[i], NULL, ((void*)leitor), (void *) escolher_ficheiro())) != 0){
  			perror("Create thread: Failed");
  			return -1;
  		}
  	}

  	for(i = 0; i < N_THREAD_READ; i++){

  		x = pthread_join(thread_array[i], (void **) &threadReturn[i]);

  		if(x != 0){
  			perror("Join thread: Failed");
  		}

  		printf("Thread N%d: %d\n", i, threadReturn[i]);
  	}

  return 0;
}