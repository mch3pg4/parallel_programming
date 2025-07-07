#include <iostream>
#include <omp.h> // Defines the use of OpenMP libraries in the code

using namespace std;

int main() {
    int num_threads;          // Number of threads set by user input
    
    cout << "Enter the number of threads: ";
    cin >> num_threads;       // Reads user input for number of threads
    
    if (num_threads <= 0) {   // Validate user input for invalid values
        cerr << "Error: Number of threads should be larger than 0" << endl;
        return 1;
    }
    
    omp_set_num_threads(num_threads); // Set thread count based on user input
    
    #pragma omp parallel      // Directive for start of parallel region
    {
        int thread_id = omp_get_thread_num(); // Gets the current thread ID
        int thread_total = omp_get_num_threads(); // Gets the total number of threads

        printf("Hello world from thread %d of %d threads. \n", thread_id, thread_total);
    }
    return 0;
}
