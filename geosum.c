// Compile: mpicc -o geosum geosum.c -lm
// Run: mpiexec -n <number_of_process> geosum

#include <math.h>
#include <stdio.h>
#include <mpi.h>
#include <time.h>

double count_a(double a, double r, int n);

int main(int argc, char* argv[]) {
    double sum = 0;
    double r = 10; // ratio
    double a = 3; // first number
    int i, rank, size;
    double local_a;

    double start, end;
    double global, duration;
    
    MPI_Init(&argc, &argv);

    start = MPI_Wtime();

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
    
    MPI_Barrier(MPI_COMM_WORLD);
    end = MPI_Wtime();
    duration = end - start;
    MPI_Reduce(&duration,&global,1,MPI_DOUBLE,MPI_MAX,0,MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Total = %.0f\n", sum);
        printf("Global Runtime = %f\n", global);
    }
    MPI_Finalize();
}

double count_a(double a, double r, int n){
    return a * pow(r, n - 1);
}