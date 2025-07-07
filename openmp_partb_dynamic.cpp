#include <iostream>
#include <omp.h>             // OpenMP header for parallelism
#include <vector>            // Vector library for C++

using namespace std;

int main() {
    const int N = 100000;    // Vector size
    
    // Initialize vectors
    vector<int> A(N, 1);
    vector<int> B(N, 2);
    vector<int> C(N);
    
    long sum = 0;           // Variable to hold sum of vectors
    
    double start_time = omp_get_wtime();    // Record start time
    
    // Parallel for loop with dynamic scheduling of chunk size 1000
    #pragma omp parallel for schedule(dynamic, 10000)
    for (int i = 0; i < N; ++i) {
        C[i] = A[i] + B[i]; 
    }
    
    // Parallel for loop using reduction for vector sum
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < N; ++i) {
        sum += C[i];
    }
    
    double end_time = omp_get_wtime();        // Record end time
    
    cout << "Dynamic schedule (10000) sum: " << sum << "\n";
    cout << "Time elapsed = " << (end_time - start_time) << " seconds\n";
    return 0;
}

