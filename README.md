# parallel-geometric-sequence

Geometric Sequence with parallel algorithm version.

## Serial Algorithm

Compile serial:

    gcc serial.c -o main -lm

Run serial:

    ./main <a> <r> <n>

## Parallel Algorithm

1. Pthread

Compile pthread:

    make

Run pthread:

    ./main <thread_count> <a> <r> <n> 

2. MPI

Compile MPI:



Run MPI: