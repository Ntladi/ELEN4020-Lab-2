#include <stdlib.h>
#include <stdio.h>
#include "commonFunctions.h"

void naive_openmp(int **mat, int mat_length)
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

void main(int argc, char* argv[])
{
	int mat_length;
	int **mat;

	if(argc == 2)
		mat_length = atoi(argv[1]);

	else
	{
		printf("Invalid run arguments\n");
		return;
	}

	mat = (int **)malloc(mat_length * sizeof(int *));

	for(int index = 0; index < mat_length; index++)
		mat[index] = (int *)malloc(mat_length * sizeof(int));

	populate(mat,mat_length);
	//printMat(mat,mat_length);
	//printf("\n");
	naive_openmp(mat,mat_length);
	//printMat(mat,mat_length);

	for (int index = 0; index < mat_length; index++)
		free(mat[index]);

	free(mat);
}
