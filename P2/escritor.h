#ifndef ESCRITOR_H
#define ESCRITOR_H

#define INDICE_ID_FILE 	7
#define CYCLES 			512 	/* 512 iteracoes por escritor */
#define PERMISSION_CODE 0644 	/* Leitura e escrita para o utilizador (6), e apenas leitura para group e world (4) */
#define N_LINES 		1024
#define N_FORK 			10 		/* 10 processos filho */

int escolher_ficheiro();
int escritor();

#endif
