#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <math.h>
#include "commonFunctions.h"
#define NUMBER_OF_THREADS 4
#define N 16
#define NUMBER_OF_BLOCKS 16

struct coord{
 int x,y;

};



int **mat;


int block_size(){ 

return sqrt((N*N)/NUMBER_OF_BLOCKS);}

void swaping(int*a, int*b);
void* transpose_each_block(void*param);
void* swap_blocks(void*param);
void block_pthread();


int main(void){

mat = (int **)malloc(N * sizeof(int *));

	for(int index = 0; index < N; index++)
		mat[index] = (int *)malloc(N * sizeof(int));



populate(mat,N);
printMat(mat,N);
printf("\n");

block_pthread();

printMat(mat,N);

for (int index = 0; index < N; index++)
		free(mat[index]);

	free(mat);


}




void swaping(int*a, int*b){


	int temp = *a;
	*a = *b;
	*b = temp;
	
}




void* transpose_each_block(void*param){

	struct coord *par = (struct coord*) param;
	int p = par->x;
	int q = par->y;
	int i,j;
	int y,z;
	for(i=p,j = q; i <(p+block_size()-1)&&j<(q+block_size()-1);i++,j++){
		for(y = i+1,z=j+1; y<(p+block_size())&&z<(q+block_size()); y++,z++){

		swaping(&mat[y][j], &mat[i][z]);
		

}
}


}



void* swap_blocks(void*param){

	struct coord *par = (struct coord*) param;
	int p = par->x;
	int q = par->y;

	for(int row = 0; row<block_size();row++){
		for(int cols = 0; cols<block_size(); cols++){

		swaping(&mat[row+p][cols+q], &mat[row+q][cols+p]);
		

}
}

}










void block_pthread(){

	
int count = 0;
struct coord pt[N][N];
pthread_t threads[NUMBER_OF_THREADS];

for(int i = 0; i<=(N-block_size()); i+=block_size()){
		for(int j=0; j<=(N-block_size()); j+=(block_size())){

			pt[i][j].x = i;
			pt[i][j].y =j;
			pthread_create(&threads[count], NULL, transpose_each_block,(void*) &pt[i][j]);
			count++;
			

			if(count==NUMBER_OF_THREADS){		
			for(int k=0; k<count; k++){
			pthread_join(threads[k],NULL);
}
			count = 0;
}
	
}
			
}

	if(count!=0)
	for(int k=0; k<count; k++){
			pthread_join(threads[k],NULL);
}



count = 0;

for(int i=0;i<=(N-2*block_size());i+=block_size()){


	for(int j = i+block_size(); j<=(N-block_size());j+=block_size()){

			pt[i][j].x = i;
			pt[i][j].y =j;

			pthread_create(&threads[count], NULL, swap_blocks,(void*) &pt[i][j]);
			count++;

	
			if(count==NUMBER_OF_THREADS){		
			for(int k=0; k<count; k++){
			pthread_join(threads[k],NULL);
}
			count = 0;
}

}
}


	if(count!=0)
	for(int k=0; k<count; k++){
			pthread_join(threads[k],NULL);
}



}
