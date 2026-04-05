#include <iostream>
#include <fstream>

using namespace std;

bool readMatrix(const char *filename, int **&matrix, int &rows, int &cols) {
    fstream f(filename, ios::in);
    if (!f) return false;
    matrix = new int*[rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
        for (int j = 0; j < cols; j++) 
            f >> matrix[i][j];
    }
    return true;
}

void printMatrix(const char *filename, int **matrix, int rows, int cols) {
    fstream F(filename, ios::out);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) F << matrix[i][j] << ' ';
        F << '\n';
    }
    F.close();
}

bool multiplyMatrices(int **a, int aRows, int aCols, int **b, int bRows, int bCols, int **&res, int &resRows, int &resCols) {
    if (aCols != bRows || !aRows || !bCols) return false; 
    resRows = aRows, resCols = bCols;
    res = new int*[aRows];
    for (int i = 0; i < resRows; i++) {
        res[i] = new int[bCols]();
        for (int j = 0; j < resCols; j++) {
            for (int k = 0; k < aCols; k++)
                res[i][j] += a[i][k] * b[k][j];
        }
    }
    return true;
}

void transposeMatrix(int **matrix, int rows, int cols, int **&res, int &resRows, int &resCols) {
    res = new int*[cols];
    for (int i = 0; i < cols; i++) {
        res[i] = new int[rows];
        for (int j = 0; j < rows; j++) 
            res[i][j] = matrix[j][i];
    }
    resCols = rows, resRows = cols;
}

void deleteMatrix(int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) 
        delete[] matrix[i];
    delete[] matrix;
}

int main() {
    int **a = nullptr, **b = nullptr, **c;
    int mA, nA, mB, nB, mC = 0, nC = 0;
    cout << "Enter the number of rows and columns of the matrix a: ";
    cin >> mA >> nA;

    if (!readMatrix("matrix_a.txt", a, mA, nA)) {
        cout << "Error! Cann't open the file matrix_a.txt";
        deleteMatrix(a, mA, nA);
        return 0;
    }

    cout << "Enter the number of rows and columns of the matrix b: ";
    cin >> mB >> nB; 
    if (!readMatrix("matrix_b.txt", b, mB, nB)) {
        cout << "Error! Cann't open the file matrix_b.txt";
        deleteMatrix(b, mB, nB);
        return 0;
    } 

    if (multiplyMatrices(a, mA, nA, b, mB, nB, c, mC, nC)) {
        cout << "The multiplication is successful.\n";
        printMatrix("matrix_c.txt", c, mC, nC);

        int **c_transposed, mct, nct;
        transposeMatrix(c, mC, nC, c_transposed, mct, nct);
        printMatrix("matrix_c_transposed.txt", c_transposed, mct, nct);
        deleteMatrix(c_transposed, mct, nct);
    }
    else cout << "The multiplication is not successful.";

    deleteMatrix(a, mA, nA);
    deleteMatrix(b, mB, nB);
    deleteMatrix(c, mC, nC);
    return 0;
}