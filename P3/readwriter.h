#ifndef READWRITER_H
#define READWRITER_H

#define INDICE_ID_FILE 	7
#define CYCLES 			512 	/* 512 iteracoes por escritor */
#define PERMISSION_CODE 0644 	/* Leitura e escrita para o utilizador (6), e apenas leitura para group e world (4) */
#define N_LINES 		1024
#define N_FORK 			10 		/* 10 processos filho */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/file.h>
#include <sys/time.h>

int escolher_ficheiro();
int escritor();
int leitor();

#endif
