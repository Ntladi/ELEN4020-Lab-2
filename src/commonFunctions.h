#ifndef COMMONFUNCTIONS_H
#define COMMONFUNCTIONS_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void populate(int **mat, int length)
{
	//srand(time(0));

	for(int i = 0; i < length; i++)
		for(int j = 0; j < length; j++)
			mat[i][j] = rand()%length + 1;
}

void printMat(int **mat, int length)
{
	for (int i = 0; i < length; ++i)
	{
		for (int j = 0; j < length; ++j)
			printf("%d ",mat[i][j]);

		printf(" \n");
	}
}
#endif