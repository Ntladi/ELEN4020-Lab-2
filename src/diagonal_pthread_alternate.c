#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>

#define NUM_THREADS  4

pthread_mutex_t mutexLU;
int matrix_size = 9;
int next_pos = 1;

typedef struct DataStore{
    int index;
    int t_id;
    int *matrix_A;
    int size;

} DataStore;

void *allocate_2D(void *input){

    struct DataStore *datastore = (struct DataStore *)input;

    int n = datastore->size;
    int nSquare = n*n;
    datastore->matrix_A = malloc(nSquare * sizeof(int *));

    for (int i = 0; i < nSquare; ++i)
    {
        datastore->matrix_A[i] = rand()%(n+1);
    }

    // free(matrix_A);

}


void *myprint2D(void *input)
{
    struct DataStore *datastore = (struct DataStore *)input;

    int *mat = datastore->matrix_A;
    int length = datastore->size;

    printf(" PrintingMatrix,%d\n", datastore->size);

    for (int index = 1; index <= length*length; index++)
    {
        printf("%d ", mat[index-1]);

        if (index%length == 0)
            printf(" \n");
    }

    // printf("\n");

    // printf(" PrintingMatrixDone\n");
    // printf(" \n");
}


void *transpose(void *args){

    struct DataStore* struct_ptr =(struct DataStore *) args;
    int position;
    int *matrix_A = struct_ptr->matrix_A;

    while(position < matrix_size){

        position = struct_ptr->index;
        for (int i = position; i < matrix_size; i++) {
            for (int j = position+1; j < matrix_size; j++) {


                int k1 = i*matrix_size + j;
                int k2 = j*matrix_size + i;

                long int temp;
                int *Row = matrix_A + k1;
                int *Col = matrix_A + k2;

                temp = *Row;
                *Row = *Col;
                *Col = temp;
                
            }

            break;
        }

        pthread_mutex_lock(&mutexLU);

        int n = next_pos++;
        struct_ptr->index = n;

        pthread_mutex_unlock(&mutexLU);

    }
}


void printTimeTaken(struct timeval start, struct timeval end)
{
    double time_taken = (end.tv_sec - start.tv_sec) * 1e6;
    time_taken = (time_taken + (end.tv_usec -  start.tv_usec)) * 1e-6;
    printf(" = %8f \n", time_taken);

}



void *pthreadOperation(void *input){
    next_pos = NUM_THREADS;

    struct DataStore *datastore = (struct datastore *) input;

    int N = datastore->size;
    struct timeval start, end;

    pthread_t threads[N];
    struct DataStore args[NUM_THREADS];

    gettimeofday(&start, NULL);

    for(int i=0;i<NUM_THREADS;i++){
        args[i].index = i;
        args[i].matrix_A = datastore->matrix_A;
        args[i].size = datastore->size;

        pthread_create(&threads[i],NULL, transpose,(void*) &args); 

    }

    for(int i=0;i<NUM_THREADS;i++){
        pthread_join(threads[i],NULL);

    }

    gettimeofday(&end, NULL);
    printTimeTaken(start, end);


}
int main() {

    printf("<<<<<<< DIAGONAL PTHREAD >>>>>>>\n");

    srand(time(0));
    int totalMatSize = 4;
    int Sizes[4] = {128, 1024, 2048, 4096};

    for (int i = 0; i < totalMatSize; ++i)
    {
        matrix_size = Sizes[i];
        DataStore *datastore = malloc(sizeof(DataStore * ));

        datastore->size = matrix_size;

        allocate_2D(datastore);
        // myprint2D(datastore);

        printf("Size [%d] ", Sizes[i]);
        pthreadOperation(datastore);
        // myprint2D(datastore);

    }

    // free(matrix);

    exit(0);
}
