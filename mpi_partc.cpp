#include <stdio.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;       // Variables for rank and number of processes
    char message[100];    // Buffer to store message

    MPI_Init(&argc, &argv);                      // Start MPI environment
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);        // Get rank (process id)
    MPI_Comm_size(MPI_COMM_WORLD, &size);        // Get total no of processes
    
    // Master process (rank: 0)
    if (rank == 0) {
        printf("Master: Hello slaves give me your messages\n");
        
        // Iterate over all slave process and send messages
        for (int i = 1; i < size; i++) {
            // Send message to process i
            sprintf(message, "Hello process %d, please respond", i);
            MPI_Send(message, strlen(message) + 1, MPI_CHAR, i, 100, MPI_COMM_WORLD);
            
        }
        
        // Receive replies from slaves
        for (int i = 1; i < size; i++) {
            MPI_Recv(message, 100, MPI_CHAR, i, 99, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Master received from process %d: %s\n", i, message);
        }
        
    } else {
        // Slaves receive message from master
        MPI_Recv(message, 100, MPI_CHAR, 0, 101, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process %d received from master: %s\n", rank, message);
        
        // Each slave process sends a different message back 
        if (rank == 1)
            strcpy(message, "Hello, I am John");
        else if (rank == 2)
            strcpy(message, "Hello, I am Mary");
        else if (rank == 3)
            strcpy(message, "Hello, I am Susan");
        else
            // Similar message for other processes
            sprintf(message, "Hello, I am process %d", rank);
        
        // Send message to master (rank: 0)
        MPI_Send(message, strlen(message)+1, MPI_CHAR, 0, 99, MPI_COMM_WORLD);
    }

    MPI_Finalize();   // End MPI environment
    return 0;
}

