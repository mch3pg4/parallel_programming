#include <iostream>
#include <omp.h>              // OpenMP header for parallelism
#include <vector>             // Vector library for C++

using namespace std;

// Function to initialize matrix with values
void initializeMatrix(vector<vector<double>>& mat, int rows, int cols, double value) {
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            mat[i][j] = value;
}

// Outer loop parallelism function
double multiplyOuterLoop(int threads, int N) {
    // Create 2D vector (matrix) of N rows and N columns
    vector<vector<double>> A(N, vector<double>(N));     // Matrix A
    vector<vector<double>> B(N, vector<double>(N));     // Matrix B
    vector<vector<double>> C(N, vector<double>(N, 0));  // Resultant Matrix C

    initializeMatrix(A, N, N, 1.0); // fill matrix A with 1
    initializeMatrix(B, N, N, 2.0); // fill matrix B with 2

    omp_set_num_threads(threads);   // Set number of threads to be used
    double start = omp_get_wtime(); // Record start time
    
    // Parallel region with outer loop parallelism
    #pragma omp parallel for
    for (int i = 0; i < N; ++i) {               // Each thread handles different row
        for (int j = 0; j < N; ++j) {           // Each column is looped through
            for (int k = 0; k < N; ++k) {       
                C[i][j] += A[i][k] * B[k][j];   // Multiply row and column
            }
        }
    }

    double end = omp_get_wtime();   // Record end time    
    return end - start;             // Return total time consumed
}

// Inner loop parallelism function
double multiplyInnerLoop(int threads, int N) {
    // Create 2D vector (matrix) of N rows and N columns
    vector<vector<double>> A(N, vector<double>(N));     // Matrix A
    vector<vector<double>> B(N, vector<double>(N));     // Matrix B
    vector<vector<double>> C(N, vector<double>(N, 0));  // Resultant Matrix C

    initializeMatrix(A, N, N, 1.0); // fill matrix A with 1
    initializeMatrix(B, N, N, 2.0); // fill matrix B with 2

    omp_set_num_threads(threads);   // Set number of threads to be used
    double start = omp_get_wtime(); // Record start time

    for (int i = 0; i < N; ++i) {
      #pragma omp parallel for 
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < N; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    double end = omp_get_wtime();   // Record end time
    return end - start;             // Return time consumed
}

int main() {
    int sizes[] = {50, 500};                   // Matrix sizes 
    int thread_counts[] = {1, 4, 8, 16};       // Thread counts

    cout << "Matrix Multiplication Timing (seconds)\n\n";

    for (int size : sizes) {
        cout << "Matrix Size: " << size << "x" << size << "\n";

        for (int t : thread_counts) {
            double time_outer = 0, time_inner = 0;

            cout << "Threads: " << t << "\n";
            cout << "  Outer Loop Times: ";
            // Run ten times for each test
            for (int i = 0; i < 10; ++i) {  
                double t_outer = multiplyOuterLoop(t, size);
                time_outer += t_outer;
                cout << t_outer << " ";
            }
            cout << "\n  Inner Loop Times: ";
            // Run ten times for each test
            for (int i = 0; i < 10; ++i) {
                double t_inner = multiplyInnerLoop(t, size);
                time_inner += t_inner;
                cout << t_inner << " ";
            }
            
            // Calculate the average of test runs
            time_outer /= 10.0;
            time_inner /= 10.0;

            cout << "\n  Average Outer Parallel: " << time_outer << "s";
            cout << "\n  Average Inner Parallel: " << time_inner << "s\n\n";
        }

        cout << "----------------------------------------\n";
    }

    return 0;
}

