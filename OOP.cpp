#include <iostream>
#include <iomanip>
#include <cmath>

// print the matrix, use a window size of 3 and right align
void printMatrix(double **list, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size+1; j++) {
            std::cout << std::setw(3) << list[i][j];
        }
        std::cout << '\n';
    }
}

// Swap two rows of a matrix
void swapRows(double* r1, double* r2, const int& size) {
    for (int col = 0; col < size; col++) {
        double temp = r1[col];
        r1[col] = r2[col];
        r2[col] = temp;
    }
}

void performGaussianElimination(double** matrix, const int& size) {
    for (int row = 0; row < size; row++) {
        if (matrix[row][row] == 0)
            swapRows(matrix[row],matrix[row+1], size);
        double row_value = matrix[row][row];
        for (int col = row; col < size+1; col++) {
            matrix[row][col] /= row_value;
        }
        
        for (int i = 0; i < size; i++) {
            if (i != row) {
                double weight = matrix[i][row]/matrix[row][row];
                for (int j = 0; j < size+1; j++) {
                    matrix[i][j] -= weight*matrix[row][j];
                }
            }
        }
        
    }
}
// 00 10 20 / 01 11 21
void backSubstitution(double** matrix, const int& size, double*solution) {
    for (int i = 0; i < size; i++) {
        solution[i+1] = matrix[i][size];
    }
}

void solveSystem(double** matrix, int n) {
    performGaussianElimination(matrix, n);
    double* solution = new double[n];
    backSubstitution(matrix, n, solution);

    std::cout << "The solution to the system of linear equations is:" << std::endl;
    std::cout << std::setprecision(6);
    for (int i = 0; i < n; i++) {
        std::cout << "x[" << i << "] = " << solution[i] << std::endl;
    }
    std::cout << std::endl;
    delete[] solution;
}

int main() {
    // create the augmented matrix
    int n = 3; // size of the matrix
    double** A = new double*[n];
    for (int i = 0; i < n; i++) {
        A[i] = new double[n+1];
    }

    // initialize the matrix with values (does not require row exchange)
    A[0][0] = 2; A[0][1] = 3; A[0][2] = -1; A[0][3] = 1;
    A[1][0] = 4; A[1][1] = 4; A[1][2] = 3; A[1][3] = 3;
    A[2][0] = 2; A[2][1] = -3; A[2][2] = 1; A[2][3] = -1;
    
    // print original matrix
    std::cout << "The original matrix (the last column is augmented) is:" << std::endl;
    printMatrix(A, n);

    // solve the system of linear equations
    solveSystem(A, n);

    // initialize the matrix with values (requires row exchange)
    A[0][0] = 0; A[0][1] = 3; A[0][2] = -1; A[0][3] = 1;
    A[1][0] = 4; A[1][1] = 4; A[1][2] = 3; A[1][3] = 3;
    A[2][0] = 2; A[2][1] = -3; A[2][2] = 1; A[2][3] = -1;
    
    // print original matrix
    std::cout << "The original matrix (the last column is augmented) is:" << std::endl;
    printMatrix(A, n);

    // solve the system of linear equations
    solveSystem(A, n);

    // free the memory used by the matrix
    for (int i = 0; i < n; i++) {
        delete[] A[i];
    }
    delete[] A;

    return 0;
}

