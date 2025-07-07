#include <iostream>
#include <mpi.h>    // Includes MPI functions

using namespace std;

int main(int argc, char** argv) {
    // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    // Get number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Print hello world from each process
    cout << "Hello, World! from process " << world_rank << " of " << world_size << endl;

    // Finalize the MPI environment
    MPI_Finalize();

    return 0;
}
