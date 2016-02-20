#include "readwriter.h"

char *cadeia[10] = {"aaaaaaaaa\n","bbbbbbbbb\n","ccccccccc\n","ddddddddd\n","eeeeeeeee\n",
				    "fffffffff\n","ggggggggg\n","hhhhhhhhh\n","iiiiiiiii\n","jjjjjjjjj\n"};

int escolher_ficheiro(int i){ /*Escolhe ficheiro entre 5, aleatoriamente*/

	char file[] = "SO2014-0.txt";

	file[INDICE_ID_FILE] += i;

	return open(file, O_RDWR | O_CREAT, PERMISSION_CODE); /*Abre file, e retorna o ID do ficheiro aberto, com as permissoes seleccionadas*/
}

int escritor(){

	int file, escolhida, i, k, j, conseguiu;

	for(i=0; i<CYCLES; i++){

		for(j = 0; j < 4; j++){

			file = escolher_ficheiro(j);

			conseguiu = flock(file, LOCK_EX | LOCK_NB);

			if(conseguiu < 0){
				/*perror("Flock on Lock: Failed.\n");*/
				close(file);
				continue;
			}

			else break;
		}

		if(conseguiu < 0){
			j=0;
			while(1){


				file = escolher_ficheiro(j%5);

				conseguiu = flock(file, LOCK_EX);

				if(conseguiu < 0){
					/*perror("Flock on Lock: Failed.\n");*/
					close(file);
					j++;
					continue;

				}

				else break;

			}

		}

		escolhida = rand() % 10; /*Linha de caracteres aleatoria*/

		for(k=0; k<N_LINES; k++){

			if(write(file, cadeia[escolhida], 10) != 10){ /*Se nao escrever 10 caracteres da erro*/
		        perror("Nao escreve linha: Erro.\n");
				flock(file, LOCK_UN);
				close(file);
				return -1;
			}
		}

		if(flock(file, LOCK_UN) < 0){
			perror("Flock on Unlock: Failed.\n");
			close(file);
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
