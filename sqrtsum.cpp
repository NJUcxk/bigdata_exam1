#include <stdio.h>
#include <mpi.h>
#include <math.h>
#include <stdlib.h>
int main(int argc, char** argv)
{
	int N=0,i;
	int my_rank, comm_sz;
	double SqrtSum = 0.0, my_sum = 0.0;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	if (my_rank == 0) {
		scanf("%d", &N);
	}
	MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);
	for (i = my_rank; i < N; i += comm_sz) {
		my_sum += sqrt(i*(i+1));
	}
	MPI_Reduce(&my_sum, &SqrtSum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	if(my_rank == 0)
		printf("SqrtSum=%f.\n", SqrtSum);
	MPI_Finalize();
}
