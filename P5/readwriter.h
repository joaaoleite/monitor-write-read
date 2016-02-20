#ifndef READWRITER_H
#define READWRITER_H

#define N_FILES 		5
#define INDICE_ID_FILE 	7
#define CYCLES 			512
#define PERMISSION_CODE_R 0444
#define PERMISSION_CODE_W 0644 	/* Leitura e escrita para o utilizador (6), e apenas leitura para group e world (4) */
#define N_LINES 		1024
#define N_THREAD_WRITE 	2
#define N_THREAD_READ	8
#define LOOP			16
#define BUG				0
#define N_BUFFER 		10
#define N_INPUT			100

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/file.h>
#include <sys/time.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>

#endif
