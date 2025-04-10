#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <stdexcept>
#include <sstream>
#include <cstdlib>
using namespace std;

//-----------------------------
// Custom Templated Matrix Class
//-----------------------------
template <typename T>
class Matrix {
private:
    size_t n;                   // Matrix size (n x n)
    vector<vector<T>> data;     // 2D storage for matrix elements
public:
    // Constructors
    Matrix() : n(0) {}
    Matrix(size_t n) : n(n), data(n, vector<T>(n, 0)) {}

    // Accessor for matrix size
    size_t size() const { return n; }

    // Get the internal matrix data
    vector<vector<T>>& getData() { return data; }
    const vector<vector<T>>& getData() const { return data; }

    // Overload stream extraction to load matrix data
    friend istream& operator>>(istream &is, Matrix<T>& m) {
        for (size_t i = 0; i < m.n; i++) {
            for (size_t j = 0; j < m.n; j++) {
                is >> m.data[i][j];
            }
        }
        return is;
    }

    // Overload stream insertion for nicely formatted output
    friend ostream& operator<<(ostream &os, const Matrix<T>& m) {
        // Adjust width for alignment (adjust if needed)
        int width = 8;
        for (size_t i = 0; i < m.n; i++) {
            for (size_t j = 0; j < m.n; j++) {
                os << setw(width) << m.data[i][j] << " ";
            }
            os << "\n";
        }
        return os;
    }

    // Overload addition operator for matrices
    Matrix<T> operator+(const Matrix<T>& other) const {
        if (n != other.n) {
            throw invalid_argument("Matrix sizes do not match for addition.");
        }
        Matrix<T> result(n);
        for (size_t i = 0; i < n; i++) {
            for (size_t j = 0; j < n; j++) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    // Overload multiplication operator for matrix multiplication
    Matrix<T> operator*(const Matrix<T>& other) const {
        if (n != other.n) {
            throw invalid_argument("Matrix sizes do not match for multiplication.");
        }
        Matrix<T> result(n);
        for (size_t i = 0; i < n; i++) {
            for (size_t j = 0; j < n; j++) {
                T sum = 0;
                for (size_t k = 0; k < n; k++) {
                    sum += data[i][k] * other.data[k][j];
                }
                result.data[i][j] = sum;
            }
        }
        return result;
    }
};

//---------------------------------------
// Function: Compute diagonal element sums
//---------------------------------------
template <typename T>
void diagonalSums(const Matrix<T>& m) {
    size_t n = m.size();
    T mainSum = 0, secSum = 0;
    for (size_t i = 0; i < n; i++) {
        mainSum += m.getData()[i][i];         // Main diagonal (top-left to bottom-right)
        secSum += m.getData()[i][n - 1 - i];    // Secondary diagonal (top-right to bottom-left)
    }
    cout << "Sum of main diagonal elements: " << mainSum << "\n";
    cout << "Sum of secondary diagonal elements: " << secSum << "\n";
}

//---------------------------------------
// Function: Swap two rows in the matrix
//---------------------------------------
template <typename T>
void swapRows(Matrix<T>& m, size_t r1, size_t r2) {
    if (r1 >= m.size() || r2 >= m.size()){
        cout << "Row indices out of bounds.\n";
        return;
    }
    swap(m.getData()[r1], m.getData()[r2]);
    cout << "Matrix after swapping rows " << r1 << " and " << r2 << ":\n";
    cout << m;
}

//---------------------------------------
// Function: Swap two columns in the matrix
//---------------------------------------
template <typename T>
void swapCols(Matrix<T>& m, size_t c1, size_t c2) {
    size_t n = m.size();
    if (c1 >= n || c2 >= n){
        cout << "Column indices out of bounds.\n";
        return;
    }
    for (size_t i = 0; i < n; i++) {
        swap(m.getData()[i][c1], m.getData()[i][c2]);
    }
    cout << "Matrix after swapping columns " << c1 << " and " << c2 << ":\n";
    cout << m;
}

//---------------------------------------
// Function: Update a specific matrix element
//---------------------------------------
template <typename T>
void updateElement(Matrix<T>& m, size_t row, size_t col, T newVal) {
    if (row >= m.size() || col >= m.size()){
        cout << "Indices out of bounds.\n";
        return;
    }
    m.getData()[row][col] = newVal;
    cout << "Matrix after updating element at (" << row << ", " << col << "):\n";
    cout << m;
}

//---------------------------------------
// Main: Process input file and test functions
//---------------------------------------
int main(){
    string filename;
    cout << "Enter the input filename: ";
    getline(cin, filename);

    ifstream fin(filename);
    if (!fin) {
        cerr << "Error opening file " << filename << "\n";
        return 1;
    }

    size_t N;
    int typeFlag;
    fin >> N >> typeFlag;

    // Depending on typeFlag, process as int (0) or double (1)
    try {
        if (typeFlag == 0) {
            // For an integer matrix
            Matrix<int> A(N), B(N);
            fin >> A >> B;
            cout << "Matrix A:\n" << A << "\n";
            cout << "Matrix B:\n" << B << "\n";

            // Add two matrices
            Matrix<int> addRes = A + B;
            cout << "A + B:\n" << addRes << "\n";

            // Multiply two matrices
            Matrix<int> multRes = A * B;
            cout << "A * B:\n" << multRes << "\n";

            // Diagonal sums of matrix A
            cout << "Diagonal sums for Matrix A:\n";
            diagonalSums(A);

            // Swap two rows (demonstration: swap first and last row)
            swapRows(A, 0, N - 1);

            // Swap two columns (demonstration: swap first and last column)
            swapCols(A, 0, N - 1);

            // Update an element (demonstration: update element at row 1, col 1 to 99)
            updateElement(A, 1, 1, 99);
        }
        else if (typeFlag == 1) {
            // For a double matrix
            Matrix<double> A(N), B(N);
            fin >> A >> B;
            cout << "Matrix A:\n" << A << "\n";
            cout << "Matrix B:\n" << B << "\n";

            // Add two matrices
            Matrix<double> addRes = A + B;
            cout << "A + B:\n" << addRes << "\n";

            // Multiply two matrices
            Matrix<double> multRes = A * B;
            cout << "A * B:\n" << multRes << "\n";

            // Diagonal sums of matrix A
            cout << "Diagonal sums for Matrix A:\n";
            diagonalSums(A);

            // Swap two rows (demonstration: swap first and last row)
            swapRows(A, 0, N - 1);

            // Swap two columns (demonstration: swap first and last column)
            swapCols(A, 0, N - 1);

            // Update an element (demonstration: update element at row 1, col 1 to 99.99)
            updateElement(A, 1, 1, 99.99);
        }
        else {
            cerr << "Invalid type flag in file. Use 0 for int or 1 for double.\n";
            return 1;
        }
    } catch (const exception &ex) {
        cerr << "Exception: " << ex.what() << "\n";
        return 1;
    }

    fin.close();
    return 0;
}
