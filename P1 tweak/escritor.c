#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "escritor.h"

#define INDICE_ID_FILE 7
#define CYCLES 5120
#define PERMISSION_CODE 0644 /* Leitura e escrita para o utilizador (6), e apenas leitura para group e world (4) */
#define N_LINES 1024

// 				   1234567890    1234567890    1234567890    1234567890    1234567890 
char *cadeia[10]={"aaaaaaaaa\n","bbbbbbbbb\n","ccccccccc\n","ddddddddd\n","eeeeeeeee\n",
				  "fffffffff\n","ggggggggg\n","hhhhhhhhh\n","iiiiiiiii\n","jjjjjjjjj\n"};


int escolher_ficheiro(){ /*Escolhe ficheiro entre 5, aleatoriamente*/

	char file[] = "SO2014-0.txt";
	int id_file = rand() % 5; 

	file[INDICE_ID_FILE] += id_file;

	return open(file, O_RDWR | O_CREAT, PERMISSION_CODE); /*Abre file, e retorna o ID do ficheiro aberto, com as permissoes seleccionadas*/
}


int escritor(){

	int file, escolhida, i, k;

	for(i=0; i<CYCLES; i++){

		file = escolher_ficheiro();
		escolhida = rand() % 10; /*Linha de caracteres aleatoria*/

		for(k=0; k<N_LINES; k++){

			if(file < 0) /*Se ficheiro invalido da erro*/
				return -1;
		 
		    if(write(file, cadeia[escolhida], 10) != 10) /*Se nao escrever 10 caracteres da erro*/
		        return -1;
		}

		close(file);
	}

	return 0;
}


int main(){

	srand(time(NULL));

	printf("ESCRITOR: %d\n", escritor());

	return 0;
}
