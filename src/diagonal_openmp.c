#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include "commonFunctions.h"

void diagonalOpenMP(int **mat, int mat_length, int num_threads);

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

	for(int index = 0; index < mat_length; index++)
		mat[index] = (int *)malloc(mat_length * sizeof(int));

	populate(mat,mat_length);
	//printMat(mat, mat_length);
	//printf("\n");
	diagonalOpenMP(mat, mat_length, num_threads);
	//printMat(mat, mat_length);

	for (int index = 0; index < mat_length; index++)
		free(mat[index]);

	free(mat);
}

void diagonalOpenMP(int **mat, int mat_length, int num_threads)
{

	omp_set_num_threads(num_threads);
	#pragma omp parallel
	{
		#pragma omp for
		for(int row = 0; row < mat_length; row ++)
			for (int col = row+1; col < mat_length; col++)
			{

				int temp = mat[row][col];
				mat[row][col] = mat[col][row];
				mat[col][row] = temp;
			}
	}
}
