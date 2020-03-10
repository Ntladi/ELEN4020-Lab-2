all: openmp_naive openmp_block openmp_diagonal pthread_block pthread_diagonal

openmp_naive: ../src/naive_openmp.c
	gcc ../src/naive_openmp.c -fopenmp -o openmp_naive

openmp_block: ../src/block_openmp.c
	gcc ../src/block_openmp.c -fopenmp -o openmp_block

openmp_diagonal: ../src/diagonal_openmp.c
	gcc ../src/diagonal_openmp.c -fopenmp -o openmp_diagonal

pthread_block: ../src/block_pthread.c
	gcc ../src/block_pthread.c -lpthread -o pthread_block

pthread_diagonal: ../src/diagonal_pthread.c
	gcc ../src/diagonal_pthread.c -lpthread -o pthread_diagonal

clean:
	rm openmp_naive openmp_block openmp_diagonal pthread_block pthread_diagonal
