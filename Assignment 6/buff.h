#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include <pthread.h>
#include <time.h>
#include <math.h>
#define THREADS 2
int fd, buf_size;
long file_size;
typedef struct{
	char* left_buf;
	char* right_buf;
	off_t left_pos;
	int len;
} thread_info;

void reverse_str(char* str);
void* reverse(void* args);