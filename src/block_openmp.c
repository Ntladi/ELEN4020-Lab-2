#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include "commonFunctions.h"

void block_openmp(int **mat, int mat_length, int num_threads, int block_length);
void swap_elements(int **mat, int max_tiles_length, int max_tiles, int tile_d, int num_threads);
void swap_tiles(int **mat, int max_tiles_length, int tile_d, int num_threads);
void edge_cases(int **mat, int mat_length, int tile_d, int num_threads);

void block_openmp(int **mat, int mat_length, int num_threads, int block_length)
{
	int tile_d = block_length;
	int max_tiles_length = (mat_length / tile_d);
	int max_tiles = max_tiles_length * max_tiles_length;

	omp_set_num_threads(num_threads);
	#pragma omp parallel
	{	
		swap_elements(mat, max_tiles_length, max_tiles, tile_d, num_threads);
		#pragma omp barrier
		swap_tiles(mat, max_tiles_length, tile_d, num_threads);
		edge_cases(mat, mat_length, tile_d, num_threads);
	}
}

void main(int argc, char* argv[])
{
	int num_threads;
	int mat_length;
	int block_length;
	int **mat;

	if(argc == 4)
	{
		num_threads = atoi(argv[1]);
		mat_length = atoi(argv[2]);
		block_length = atoi(argv[3]);
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
	block_openmp(mat,mat_length,num_threads, block_length);
	printMat(mat, mat_length);

	for (int index = 0; index < mat_length; index++)
		free(mat[index]);

	free(mat);
}

void swap_elements(int **mat, int max_tiles_length, int max_tiles, int tile_d, int num_threads)
{
	#pragma omp for
	for(int tile = 0; tile < max_tiles; tile++)
	{
		int row_start = (tile / max_tiles_length) * tile_d;
		int col_start = (tile % max_tiles_length) * tile_d;
		int row_end = row_start + tile_d;
		int col_end = col_start + tile_d;

		for(int row = row_start, col_offset = 1; row < row_end; row++, col_offset++)
			for(int col = col_start + col_offset, index_offset = 1; col < col_end; col++, index_offset++)
			{
				int temp = mat[row][col];
				mat[row][col] = mat[row + index_offset][col - index_offset];
				mat[row + index_offset][col - index_offset] = temp;
			}
	}
}

void swap_tiles(int **mat, int max_tiles_length, int tile_d, int num_threads)
{
	#pragma omp for
	for(int tile1 = 0; tile1 < max_tiles_length; tile1++)
		for(int tile2 = tile1+1; tile2 < max_tiles_length; tile2++)	
		{
			int row_start_1 = tile1 * tile_d;
			int col_start_1 = (tile2 % max_tiles_length) * tile_d;
			int row_start_2 = col_start_1;
			int col_start_2 = row_start_1;

			int row_end = row_start_1 + tile_d;
			int col_end = col_start_1 + tile_d;

			for(int row1 = row_start_1, row2 = row_start_2; row1 < row_end; row1++, row2++)	
				for(int col1 = col_start_1, col2 = col_start_2; col1 < col_end; col1++, col2++)
				{
					int temp = mat[row1][col1];
					mat[row1][col1] = mat[row2][col2];
					mat[row2][col2] = temp;
				}	
		}
}

void edge_cases(int **mat, int mat_length, int tile_d, int num_threads)
{
	if(mat_length % tile_d != 0)
	{
		int edge = (mat_length - mat_length%tile_d);
		omp_set_num_threads(num_threads);


		#pragma omp for collapse(2)
		for(int row = edge; row < mat_length; row++)
			for(int col = 0; col < mat_length; col++)
			{
				int temp = mat[row][col];
				mat[row][col] = mat[col][row];
				mat[col][row] = temp;
			}

		for(int row = edge; row < mat_length; row ++)
			for(int col = edge; col < row; col++)
			{
				int temp = mat[row][col];
				mat[row][col] = mat[col][row];
				mat[col][row] = temp;				
			}
	}

}
