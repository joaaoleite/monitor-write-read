#include "readwriter.h"

char *cadeia[10] = {"aaaaaaaaa\n","bbbbbbbbb\n","ccccccccc\n","ddddddddd\n","eeeeeeeee\n",
				    "fffffffff\n","ggggggggg\n","hhhhhhhhh\n","iiiiiiiii\n","jjjjjjjjj\n"};

int leitor(char id_file){

	int file, i = 0;
	char linha[10], primeira[10], filename[] = "SO2014-0.txt";

	filename[INDICE_ID_FILE] = id_file;

	file = open(filename, O_RDWR | O_CREAT, PERMISSION_CODE);
	
	if (file < 0){
		perror("Open: Failed.\n");
		return -1;
	}

	if(flock(file, LOCK_SH) < 0){
		perror("Flock on Lock: Failed.\n");
		close(file);
		return -1;
	}

	if(read(file, primeira, 10) < 10){	/*Le a primeira linha para comparacao*/
		perror("First Read: Failed.\n");
		flock(file, LOCK_UN);
		close(file);
		return -1;
	} 

	while(read(file, linha, 10) != 0){ /*Enquanto houver linhas no ficheiro*/

		if(strncmp(primeira, linha, 10) != 0){
			perror("Linha nao corresponde: Erro.\n");	/*Se linha diferente da primeira da erro*/
			flock(file, LOCK_UN);
			close(file);
			return -1;
		}

		i++;
	}

	if(flock(file, LOCK_UN) < 0){
		perror("Flock on Unlock: Failed.\n");
		close(file);
		return -1;
	}

	close(file);

	if(i != (N_LINES - 1)){ /*Se acabou o ficheiro, sucesso*/
		perror("Não acabou o ficheiro: Erro.\n");
		return -1;
	}
	
	return 0;
}


int main(int argc, char **args){

	if(argc != 2){
		perror("Invalid number of arguments.");
		return -1;
	}

	else
		return leitor(args[1][0]);
}
