#include <iostream>
#include <vector>

using namespace std;
int n = 0;
int k = 0;
int foundSolutions = 0;
int targetSolution = 0;

vector<vector<int>> solution;
vector<int> diagSums(2 , 0); // [0] es diagonal ascendente [1] es descendente
vector<int> colSums;

vector<vector<int>> matrix;
vector<bool> isThisNumberUsed;

void printMatrix(vector<vector<int>> &matrix) { // ROBA2 DE GEEKS4GEEKS
    for (auto &row: matrix) {
        for (auto &column: row) {
            cout << column << " ";
        }
        cout << endl;
    }
}

bool canComplete(int i, int j, int rowSum) {
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
    for (int idx = 0; idx < n*n && (neededMinsRow > 0 || neededMinsCol > 0 || neededMinsDescDiag > 0); idx++) {
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

void cuadradoMagico(int i, int j, int rowSum) {
    if (foundSolutions == targetSolution) {
        return;
    }

    if (j == n && i == n - 1) { // Llegamos al final de la matrix
        if (rowSum == k && colSums[j-1] == k && diagSums[0] == k && diagSums[1] == k) {
            solution = matrix;
            foundSolutions++;
        }
        return;
    }
    if (j == n) { // Bajar a la siguiente fila
        if (rowSum == k && colSums[j-1] < k && diagSums[0] <= k && diagSums[1] <= k)
            return cuadradoMagico(i + 1, 0, 0);
        return;
    }
    if (i == n-1 && j != 0 && colSums[j-1] != k) return; // Si estoy en la ultila fila chequeo que las columnas estén bien

    if (j != 0 && colSums[j-1] > k) return; // Chequeo columnas

    if (rowSum >= k) return; // Si me pasé con la fila

    if (diagSums[0] > k || diagSums[1] > k) return; // Si me paso con una diagonal

    if (matrix[n-1][n-1] == 0 && diagSums[0] == k) return; // Si una diagonal es k pero no la completé

    if (matrix[n-1][0] == 0 && diagSums[1] == k) return; // Si una diagonal es k pero no la completé

    //if (!canComplete(i, j, rowSum)) return; // Poda para ver si con los mínimos elementos disponibles puedo no pasarme

    // Notar que las soluciones se intentan en orden y se guardan en orden
    for (int idx = 0; idx < n*n; idx++) {
        if (isThisNumberUsed[idx] == false) { // ¿Está en uso idx+1 en esta rama?
            matrix[i][j] = idx + 1;
            isThisNumberUsed[idx] = true; // idx + 1 en uso
            colSums[j] += idx + 1;
            if (i == j) diagSums[0] += idx + 1;
            if (n - 1 - i == j) diagSums[1] += idx + 1;
            cuadradoMagico(i, j + 1, rowSum + idx + 1);
            colSums[j] -= idx + 1; // Backtrack
            if (i == j) diagSums[0] -= idx + 1; // Backtrack
            if (n - 1 - i == j) diagSums[1] -= idx + 1; // Backtrack
            matrix[i][j] = 0; //Backtrack
            isThisNumberUsed[idx] = false; // Backtrack
        }
    }
}

int main(int argc, char** argv) {
    cin >> n >> targetSolution;
    k = (n * n * n + n) / 2;
    colSums = vector<int> (n, 0);
    matrix = vector<vector<int>>(n, vector<int>(n, 0));
    isThisNumberUsed = vector<bool>(n * n, false);
    cuadradoMagico(0, 0, 0);
    if (targetSolution != foundSolutions)
        cout << "-1" << endl;
    else printMatrix(solution);
    return 0;
}
