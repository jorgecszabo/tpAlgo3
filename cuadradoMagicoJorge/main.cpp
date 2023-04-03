#include <iostream>
#include <vector>

using namespace std;
const int n = 3;
const int k = (n * n * n + n) / 2;
int prevRowSum = 0;
int prevColSum[n] = {0};

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
/*
int diagSumUntilij(const vector<vector<int>> &matrix, int i, int j) {
    int res = 0;
    for (int idx = 0; idx < i || idx < j; idx++)
        res += matrix[idx][idx];
    return res;
}*/

int descDiagSum(const vector<vector<int>> &matrix) {
    int res = 0;
    for (int idx = 0; idx < matrix.size() && matrix[idx][idx] != 0; idx++)
        res += matrix[idx][idx];
    return res;
}

int ascDiagSum(const vector<vector<int>> &matrix) {
    int res = 0;
    for (int idx = 0; idx < matrix.size() && matrix[idx][matrix.size() - 1 - idx] != 0; idx++)
        res += matrix[idx][matrix.size() - 1 - idx];
    return res;
}

bool canCompleteRow(const vector<vector<int>> &matrix, const vector<bool> &isThisNumberUsed, int i, int j) {
    int neededMins = matrix.size() - j;
    vector<int> mins;
    for (int idx = 0; idx < isThisNumberUsed.size() && neededMins > 0; idx++) {
        if (isThisNumberUsed[idx] == false) {
            mins.push_back(idx + 1);
            neededMins--;
        }
    }
    int sum = 0;
    for (int idx = 0; idx < j; idx++)
        sum += matrix[i][idx];
    for (int e : mins)
        sum += e;
    return sum <= k;
}

bool canCompleteCol(const vector<vector<int>> &matrix, const vector<bool> &isThisNumberUsed, int i, int j) {
    int neededMins = matrix.size() - i;
    vector<int> mins;
    for (int idx = 0; idx < isThisNumberUsed.size() && neededMins > 0; idx++) {
        if (isThisNumberUsed[idx] == false) {
            mins.push_back(idx + 1);
            neededMins--;
        }
    }
    int sum = 0;
    for (int idx = 0; idx < i; idx++)
        sum += matrix[idx][j];
    for (int e : mins)
        sum += e;
    return sum <= k;
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
    if (j == n && i == n - 1)  { // Llegamos al fin de la matrix
        if (isItMagic(matrix)) {
            solutions.push_back(matrix); // Guardo la solución correcta
            return 1;
        } else return 0;
    }
    prevRowSum = j > 0 ? prevRowSum + matrix[i][j-1] : 0;
    prevColSum[]
    int ascDiagonalSum = ascDiagSum(matrix);
    int descDiagonalSum = descDiagSum(matrix);
    bool canComplete = canCompleteCol(matrix, isThisNumberUsed, i, j) && canCompleteRow(matrix, isThisNumberUsed, i, j);

    if (j == n) {
        if (prevRowSum != k && prevColSum[j] < k && ascDiagonalSum <= k && descDiagonalSum <= k)
            return cuadradoMagico(matrix, isThisNumberUsed, i + 1, 0);
        return 0;
    }
    if (rowSum >= k || colSum >= k || ascDiagonalSum > k || descDiagonalSum > k || !canComplete) //Pero no llegamos al final
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
