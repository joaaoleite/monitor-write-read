#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include "leitor.h"

#define INDICE_ID_FILE 7
#define PERMISSION_CODE 0644 /* Leitura e escrita para o utilizador (6), e apenas leitura para group e world (4) */
#define LINES_LEFT 1023

int escolher_ficheiro(int id){ /*Escolhe ficheiro entre 5, aleatoriamente*/

	char file[] = "SO2014-0.txt";

	file[INDICE_ID_FILE] += id;

	return open(file, O_RDWR | O_CREAT, PERMISSION_CODE); /*Abre file, e retorna o ID do ficheiro aberto, com as permissoes seleccionadas*/
}


int leitor(int id){

	int file, i=0;
	char linha[10], primeira[10];

	file = escolher_ficheiro(id);

	read(file,primeira,10); /*Le a primeira linha para comparacao*/

	while(read(file,linha,10)>0 ){ /*Enquanto houver linhas no ficheiro*/

		if(strncmp(primeira,linha,10) != 0) /*Se linha diferente da primeira da erro*/
			return -1;
		i++;
	}

	if(i==LINES_LEFT) /*Se acabou o ficheiro, sucesso*/
		return 0;
	
	else
		return -1;
	
}


int main(){


	for(int i=0; i<5; i++){
		printf("LEITOR: %d\n", leitor(i));
	}

	

	return 0;
}



