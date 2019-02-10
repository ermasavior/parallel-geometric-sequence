#include <math.h>
#include <stdio.h>
#include <mpi.h>

double count_a(double a, double r, int n);

int main(int argc, char* argv[]) {
    double sum = 0;
    double r = 4;
    double a = 2;
    int i, rank, size;
    double local_a;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    local_a = a * pow(r, rank);
    if(rank != 0) {
        MPI_Send(&local_a, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    } else {
        sum = local_a;
        for (i = 1; i < size; i++) {
            MPI_Recv(&local_a, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            sum += local_a;
        }
    }

    if (rank == 0) {
        printf("Total = %f\n", sum);
    }

    MPI_Finalize();
}

double count_a(double a, double r, int n){
    return a * pow(r, n - 1);
}