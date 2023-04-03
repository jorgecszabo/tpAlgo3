#include <iostream>
#include <vector>

using namespace std;
const int n = 3;
const int k = (n * n * n + n) / 2;

vector<vector<vector<int>>> solutions;

unsigned long long int iter = 0;

void printMatrix(vector<vector<int>> &matrix) { // ROBA2 DE GEEKS4GEEKS
    for (auto &row: matrix) {
        for (auto &column: row) {
            cout << column << " ";
        }
        cout << endl;
    }
    cout << "END OF MATRIX" << endl;
}


int sumRowUntilj(const vector<vector<int>> &matrix, int i, int j) {
    int res = 0;
    for (int idx = 0; idx < j; idx++)
        res += matrix[i][idx];
    return res;
}

int sumColUntili(const vector<vector<int>> &matrix, int i, int j) {
    int res = 0;
    for (int idx = 0; idx < i; idx++)
        res += matrix[idx][j];
    return res;
}

int diagSumUntilij(const vector<vector<int>> &matrix, int i, int j) {
    int res = 0;
    for (int idx = 0; idx < i || idx < j; idx++)
        res += matrix[idx][idx];
    return res;
}

bool isItMagic(const vector<vector<int>> &matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        int target = 0;
        for (int j = 0; j < matrix.size(); j++)
            target += matrix[i][j];
        if (target != k)
            return false;
    }
    for (int j = 0; j < matrix.size(); j++) {
        int target = 0;
        for (int i = 0; i < matrix.size(); i++)
            target += matrix[i][j];
        if (target != k)
            return false;
    }
    int target = 0;
    for (int i = 0; i < matrix.size(); i++) {
        target += matrix[i][i];
    }
    if (target != k)
        return false;
    target = 0;
    for (int i = 0; i < matrix.size(); i++) {
        target += matrix[i][matrix.size() - 1 - i];
    }
    if (target != k)
        return false;
    return true;
}

int cuadradoMagico(vector<vector<int>> &matrix, vector<bool> &isThisNumberUsed, int i, int j) {
    iter++;
    if (j == n && i == n - 1) // Llegamos al fin de la matrix
        if (isItMagic(matrix)) {
            solutions.push_back(matrix); // Guardo la solución correcta
            return 1;
        }
    int rowSum = sumRowUntilj(matrix, i, j);
    int colSum = sumColUntili(matrix, i, j);
    int diagonalSum = diagSumUntilij(matrix, i, j);
    if (j == n) {
        if (rowSum == k && colSum < k && diagonalSum < k)
            return cuadradoMagico(matrix, isThisNumberUsed, i + 1, 0);
        return 0;
    }
    if (rowSum >= k || colSum >= k || diagonalSum >= k) //Pero no llegamos al final
        return 0;
    int res = 0;
    // Notar que las soluciones se intentan en orden y se guardan en orden
    for (int idx = 0; idx < isThisNumberUsed.size(); idx++) {
        if (isThisNumberUsed[idx] == false) { // ¿Está en uso idx+1 en esta rama?
            matrix[i][j] = idx + 1;
            isThisNumberUsed[idx] = true; // idx + 1 en uso
            res += cuadradoMagico(matrix, isThisNumberUsed, i, j + 1);
            matrix[i][j] = 0; //Backtrack
            isThisNumberUsed[idx] = false; // Backtrack
        }
    }
    return res;
}

int main() {
    vector<vector<int>> matrix(n, vector<int>(n, 0));
    vector<bool> isThisNumberUsed(n * n, false);
    cout << cuadradoMagico(matrix, isThisNumberUsed, 0, 0) << " magic squares of size " << n << endl;
    cout << "Iterations: " << iter << endl;
    for (auto sol: solutions)
        printMatrix(sol);

    return 0;
}
