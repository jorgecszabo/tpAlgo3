#include <iostream>
#include <vector>

using namespace std;
const int n = 4;
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

bool canComplete(const vector<vector<int>> &matrix, const vector<bool> &isThisNumberUsed, int i, int j, int rowSum, const vector<int> &colSums, const vector<int> &diagSums) {
    int neededMinsRow = n - j;
    int neededMinsCol = n - i;
    int neededMinsDescDiag;
    if (j > i) {
        neededMinsDescDiag = i;
    } else {
        neededMinsDescDiag = max(0, i - 1);
    }
    neededMinsDescDiag = n-1-neededMinsDescDiag;

    int minSumRow = 0;
    int minSumCol = 0;
    int minSumDescDiag = 0;
    for (int idx = 0; idx < isThisNumberUsed.size() && (neededMinsRow > 0 || neededMinsCol > 0 || neededMinsDescDiag > 0); idx++) {
        if (isThisNumberUsed[idx] == false) {
            if (neededMinsRow > 0) {
                minSumRow += idx + 1;
                neededMinsRow--;
            }
            if (neededMinsCol > 0) {
                minSumCol += idx + 1;
                neededMinsCol--;
            }
            if (neededMinsDescDiag > 0) {
                minSumDescDiag += idx + 1;
                neededMinsDescDiag--;
            }
        }
    }
    int descDiagSum = diagSums[0] + minSumDescDiag;
    rowSum += minSumRow;
    int colSum = colSums[j] + minSumCol;
    return rowSum <= k && colSum <= k && descDiagSum <= k;
}

int cuadradoMagico(vector<vector<int>> &matrix, vector<bool> &isThisNumberUsed, int i, int j, int rowSum, vector<int> &colSums, vector<int> &diagSums) {
    iter++;
    if (j == n && i == n - 1) { // Llegamos al final de la matrix
        bool res = rowSum == k && colSums[j-1] == k && diagSums[0] == k && diagSums[1] == k;
        if (res) solutions.push_back(matrix);
        return res;
    }
    if (j == n) { // Bajar a la siguiente fila
        if (rowSum == k && colSums[j-1] < k && diagSums[0] <= k && diagSums[1] <= k)
            return cuadradoMagico(matrix, isThisNumberUsed, i + 1, 0, 0, colSums, diagSums);
        return 0;
    }
    if (i == n-1 && j != 0 && colSums[j-1] != k) return 0; // Si estoy en la ultila fila chequeo que las columnas estén bien

    if (j != 0 && colSums[j-1] > k) return 0; // Chequeo columnas

    if (rowSum >= k) return 0; // Si me pasé con la fila

    if (diagSums[0] > k || diagSums[1] > k) return 0; // Si me paso con una diagonal

    if (matrix[n-1][n-1] == 0 && diagSums[0] == k) return 0; // Si una diagonal es k pero no la completé

    if (matrix[n-1][0] == 0 && diagSums[1] == k) return 0; // Si una diagonal es k pero no la completé

    if (!canComplete(matrix, isThisNumberUsed, i, j, rowSum, colSums, diagSums)) return 0; // Poda para ver si con los mínimos elementos disponibles puedo no pasarme

    int res = 0;
    // Notar que las soluciones se intentan en orden y se guardan en orden
    for (int idx = 0; idx < isThisNumberUsed.size(); idx++) {
        if (isThisNumberUsed[idx] == false) { // ¿Está en uso idx+1 en esta rama?
            matrix[i][j] = idx + 1;
            isThisNumberUsed[idx] = true; // idx + 1 en uso
            colSums[j] += idx + 1;
            if (i == j) diagSums[0] += idx + 1;
            if (n - 1 - i == j) diagSums[1] += idx + 1;
            res += cuadradoMagico(matrix, isThisNumberUsed, i, j + 1, rowSum + idx + 1, colSums, diagSums);
            colSums[j] -= idx + 1; // Backtrack
            if (i == j) diagSums[0] -= idx + 1; // Backtrack
            if (n - 1 - i == j) diagSums[1] -= idx + 1; // Backtrack
            matrix[i][j] = 0; //Backtrack
            isThisNumberUsed[idx] = false; // Backtrack
        }
    }
    return res;
}

int main() {
    vector<vector<int>> matrix(n, vector<int>(n, 0));
    vector<bool> isThisNumberUsed(n * n, false);
    vector<int> colSums(n, 0);
    vector<int> diagSums(2 , 0); // [0] es diagonal ascendente [1] es descendente
    cout << cuadradoMagico(matrix, isThisNumberUsed, 0, 0, 0, colSums, diagSums) << " magic squares of size " << n << endl;
    cout << "Iterations: " << iter << endl;
    //for (auto sol: solutions)
    //    printMatrix(sol);

    return 0;
}
