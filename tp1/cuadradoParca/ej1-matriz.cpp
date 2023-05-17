#include <bits/stdc++.h>

using namespace std;

#define N 3
uint16_t numeroMagico = (N*N*N + N)/2; // Formula del numero magico
int sumaGlobal = 0;
int llamados = 0;

list<vector<vector<int>>> cuadrados;

void printCuadrado(vector<vector<int>> cua) {
    cout << "-- cuadradito --" << endl;
    for (int i=0; i < N; i++) {
        for (int j=0; j < N; j++) {
            cout << cua[i][j] << ", ";
        }
        cout << "\n";
    }
    cout << "--- --- --- \n";
}

void BT(int n, vector<vector<int>> cuadrado, int i, int j) {
    // llamados++;
    for (int x=1; x <= n*n; x++) {
        bool esta = false;
        for (int Q=0; Q < n; Q++) {
            if (count(cuadrado[Q].begin(), cuadrado[Q].end(), x) != 0) {
                esta = true;
                break;
            }
        }
        if (!esta) {
            cuadrado[i][j] = x;
            int fila = 0;
            int col = 0;
            int diagAsc = 0;
            int diagDes = 0;
            for (int z=0; z < n; z++) {
                fila += cuadrado[i][z];
            }
            for (int z=0; z < n; z++) {
                col += cuadrado[z][j];
            }
            for (int z=0; z < n; z++) {
                diagDes += cuadrado[z][z];
            }
            if (i == n-1 && j == n-1) {
                for (int z=0; z < n; z++) {
                    diagAsc += cuadrado[n-1-z][z];
                }
                if (diagAsc != numeroMagico) {
                    goto jaja;
                }
            }
            // Si completo una fila o columna y no suma el numero magico podo.
            if ((j == n-1 && fila != numeroMagico) ||
                (i == n-1 && col != numeroMagico)) {
                ;
            } else if ( fila <= numeroMagico &&
                        col <= numeroMagico &&
                        diagAsc <= numeroMagico &&
                        diagDes <= numeroMagico) {
                if (i == n-1 && j == n-1) {
                    if (fila == numeroMagico &&
                        col == numeroMagico &&
                        diagAsc == numeroMagico &&
                        diagDes == numeroMagico) {
                        sumaGlobal += 1;
                        cuadrados.push_back(cuadrado);
                    }
                } else {
                    if (j < n-1) {
                        BT(n, cuadrado, i, j+1);
                    } else {
                        BT(n, cuadrado, i+1, 0);
                    }
                }
            }
            jaja:
            cuadrado[i][j] = 0;
        }
    }
}


int contarCuadradosMagicos(int n) {
    vector<vector<int>> cuadrado(n, vector<int>(n, 0));
    sumaGlobal = 0;
    BT(n, cuadrado, 0, 0);
    return sumaGlobal;
}



int main() {
    auto t2 = chrono::high_resolution_clock::now();
    cout << "cuadrados magicos: " << contarCuadradosMagicos(N) << endl;
    cout << "llamados: " << llamados << endl;
    auto t3 = chrono::high_resolution_clock::now();
    cout << "Con podas tomo: " << chrono::duration_cast<chrono::milliseconds>(t3-t2).count() << "ms" << endl << endl;

    printCuadrado(cuadrados.front());
}