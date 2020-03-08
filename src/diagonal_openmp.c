#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include "commonFunctions.h"

void diagonalOpenMP(int **mat, int mat_length, int num_threads)
{
	#pragma omp parallel for
	{
		for (int i = 0; i < mat_length; ++i)
		{
			for (int j = i; j < mat_length; ++j)
			{
				int temp = mat[i][j];
				mat[i][j] = mat[j][i];
				mat[j][i] = temp; 
			}
		}
	}
}

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
	printMat(mat, mat_length);
	diagonalOpenMP(mat, mat_length);
	printMat(mat, mat_length);

	for (int index = 0; index < mat_length; index++)
		free(mat[index]);

	free(mat);
}
