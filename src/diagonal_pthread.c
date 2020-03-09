#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "commonFunctions.h"

int thread_id = 0;
pthread_mutex_t lock;

struct data {
	int **mat;
	int mat_length;
	int num_threads;
	int thread_id;
};

void diagonal_pthreads(int **mat, int mat_length, int num_threads);
void* diagonal_pointer(void *input);

void main(int argc, char* argv[])
{
	int num_threads;
	int mat_length;
	int **mat;

	if(argc == 3)
	{
		num_threads = atoi(argv[1]);
		mat_length = atoi(argv[2]);
	}
	else
	{
		printf("Invalid run arguments\n");
		return;
	}

	mat = (int **)malloc(mat_length * sizeof(int *));

	for(int index = 0; index < mat_length; index ++)
		mat[index] = (int *)malloc(mat_length * sizeof(int));

	populate(mat,mat_length);
	//printMat(mat, mat_length);
	//printf("\n");
	diagonal_pthreads(mat,mat_length,num_threads);
	//printMat(mat,mat_length);

	for (int index = 0; index < mat_length; index ++)
		free(mat[index]);

	free(mat);
}

void diagonal_pthreads(int **mat, int mat_length, int num_threads)
{
	pthread_t threads[num_threads];

	struct data values;
	values.mat = mat;
	values.mat_length = mat_length;
	values.num_threads = num_threads;

	for(int index = 0; index < num_threads; index ++)
		pthread_create(&threads[index], NULL, diagonal_pointer, &values);

	for(int index = 0; index < num_threads; index ++)
		pthread_join(threads[index], NULL);
}

void* diagonal_pointer(void *input)
{

	struct data values = *((struct data*) input);

	pthread_mutex_lock(&lock);
	values.thread_id = thread_id;
	thread_id++;
	pthread_mutex_unlock(&lock);

	for(int row = values.thread_id; row < values.mat_length; row+=values.num_threads)
		for (int col = row+1; col < values.mat_length; col++)
		{
			int temp = values.mat[row][col];
			values.mat[row][col] = values.mat[col][row];
			values.mat[col][row] = temp;
		}

	pthread_exit(0);
}
