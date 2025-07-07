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
    
    int user_limit; // variable to store user defined processes
    
    if (world_rank == 0) {
      cout << "Total MPI processes started: " << world_size << endl;
      cout << "Enter number of processes to print Hello World (<= "<< world_size << "): " ;
      cin >> user_limit;
      }
    
    // Broadcast user defined limit from root to all processes
    MPI_Bcast(&user_limit, 1, MPI_INT, 0, MPI_COMM_WORLD);
    
    if (world_rank < user_limit) {
      // Print hello world from each process
      cout << "Hello, World! from process " << world_rank << " of " << user_limit << endl;
    }
    
    // Finalize the MPI environment
    MPI_Finalize();

    return 0;
}
