#include "readwriter.h"

char *cadeia[10] = {"aaaaaaaaa\n","bbbbbbbbb\n","ccccccccc\n","ddddddddd\n","eeeeeeeee\n",
				    "fffffffff\n","ggggggggg\n","hhhhhhhhh\n","iiiiiiiii\n","jjjjjjjjj\n"};
Arg vec_struct[K];
char mensagens[K][2]={"a","B","c","d","E","f","g","h","J","i"};

long escolher_ficheiro(){ /*Escolhe ficheiro entre 5, aleatoriamente*/

	long id_file = rand() % 5;
	
	return id_file;
}

int leitor(void *arg){

	int file, i = 0;
	long res;
	char linha[10], primeira[10], filename[] = "SO2014-0.txt";
	int posicao=((Arg*) arg)->posicao;
	int totallinhas=N_LINES;
	int k = K;
	int p;

	int nlinhas = totallinhas/k;

	printf("%s\n", ((Arg*) arg)->mensagem);
	if((totallinhas-(posicao+nlinhas))<nlinhas){
		nlinhas+=totallinhas%nlinhas;
	}
	
	int id_ficheiro = FICHEIRO;

	filename[INDICE_ID_FILE] += id_ficheiro;


	file = open(filename, O_RDWR | O_CREAT, PERMISSION_CODE);
	p=posicao*10;
	lseek(file,p,SEEK_SET);
	
	if (file < 0){
		perror("Open: Failed.\n");
		return -1;
	}

	if(read(file, primeira, 10) < 10){	/*Le a primeira linha para comparacao*/
		perror("First Read: Failed.\n");
		close(file);
		return -1;
	} 

	for(i=0; i<nlinhas; i++){
		read(file, linha, 10);
		if(strncmp(primeira, linha, 10) != 0){
			perror("Linha nao corresponde: Erro.\n");	/*Se linha diferente da primeira da erro*/
			close(file);
			return -1;
		}
	}
	close(file);

	if(i != nlinhas){ /*Se acabou o ficheiro, sucesso*/
		perror("Não acabou o ficheiro: Erro.\n");
		return -1;
	}
	return 0;
}

int main(){

	int i, threadReturn[K];
	pthread_t thread_array[K];
	int posicao=0;
	int nlinhas=N_LINES/K;
	int soma=0;

	srand(time(NULL));

  	for(i = 0; i < K; i++){

  		vec_struct[i].posicao = posicao;
  		strcpy(vec_struct[i].mensagem, mensagens[i]);

  		if(pthread_create(&thread_array[i], NULL, (void *) leitor, (void *) &vec_struct[i]) != 0){
  			perror("Create thread: Failed");
  			return -1;
  		}
  		posicao+=nlinhas;
  	}

  	for(i = 0; i < K; i++){

  		if((pthread_join(thread_array[i], (void **) &threadReturn[i])) != 0){
  			perror("Join thread: Failed");
  		}

  		printf("Thread N%d: %d\n", i, threadReturn[i]);
  		soma+=threadReturn[i];
  	}

  return 0;
}