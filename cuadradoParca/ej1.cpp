#include <bits/stdc++.h>

using namespace std;

#define N 4
int numeroMagico = (N*N*N + N)/2; // Formula del numero magico
int llamados = 0;

vector<int> cuadrado(N*N);
list<vector<int>> cuadrados;

void printCuadrado(vector<int> cua) {
    cout << "-- cuadradito --" << endl;
    for (int i=0; i < N; i++) {
        for (int j=0; j < N; j++) {
            cout << cua[i*N+j] << ", ";
        }
        cout << "\n";
    }
    cout << "--- --- --- \n";
}


int cota(int faltan, vector<bool>& usado, int& n) {
    int cota = numeroMagico;
    int x = 0;
    int y = n*n;
    while (x < faltan) {
        if (!usado[y]) {
            cota -= y;
            x++;
        }
        y--;
    }
    return cota;
}

int BT(int n, vector<bool> usado, int k) {
    llamados++;
    int res = 0;
    for (int i=1; i <= n*n; i++) {
        if (!usado[i]) {
            cuadrado[k] = i; // Hago todos los calculos asumiendo que ya coloque el numero.
            usado[i] = true;
            // Cuando suman fila y columna actual
            int fila = 0;
            int columna = 0;
            int diagAsc = 0;
            int diagDes = 0;
            for (int j=0; j < n; j++) {
                fila += cuadrado[k-k%n+j];
                columna += cuadrado[k%n + j*n];
                diagDes += cuadrado[j*(n+1)];
                diagAsc += cuadrado[(n-1)*(j+1)];
            }
            // Cotas inferiores.
            int faltanFila = n - k%n - 1;
            int cotaInfFila = cota(faltanFila, usado, n);
            int faltanColumna = ceil(n - k/n - 1);
            int cotaInfCol = cota(faltanColumna, usado, n);
            int faltanDiagonalDes = n - ceil(k/(n+1)) - 1;
            int cotaInfDiagDes = cota(faltanDiagonalDes, usado, n);
            int faltanDiagonalAsc = n - ceil(k/(n-1));
            int cotaInfDiagAsc = cota(faltanDiagonalAsc, usado, n);

            // Aplico podas
            if ((fila < cotaInfFila) ||
                (columna < cotaInfCol) ||
                (diagDes < cotaInfDiagDes) ||
                (diagAsc < cotaInfDiagAsc) ||
                ((k == n*n-n) && diagAsc != numeroMagico) || // Completo la diagonal ascendente y suma distinto a numero magico.
                (k%n == n-1 && fila != numeroMagico) || // Completo una fila y suma distinto.
                (k >= (n*n-n) && columna != numeroMagico) || // Completo columna y suma distinto. 
                (k == n*n-1 && diagDes != numeroMagico) // Suma diagonal descendiente y suma distinto.
                ) {
                ;
            } else if ( fila <= numeroMagico &&
                        columna <= numeroMagico &&
                        diagAsc <= numeroMagico &&
                        diagDes <= numeroMagico) {
                if (k == n*n-1) {
                    res += 1;
                    cuadrados.push_back(cuadrado);
                } else {
                    res += BT(n, usado, k+1);
                }
            }
            cuadrado[k] = 0;
            usado[i] = false;
        }
    }
    return res;
}

int contarCuadradosMagicosOrden(int n) {
    vector<int> cuadrado (n*n, 0);
    vector<bool> usado(n*n+1, false);
    return BT(n, usado, 0);
}

int main() {
    auto t1 = chrono::high_resolution_clock::now();
    int cantidad = contarCuadradosMagicosOrden(N);
    auto t2 = chrono::high_resolution_clock::now();
    cout << "Cantidad de cuadrados magicos: " << cantidad << endl;
    cout << "Llamados recursivos: " << llamados << endl;
    cout << "Tomo: " << chrono::duration_cast<chrono::milliseconds>(t2-t1).count() << "ms" << endl << endl;
    cout << "- Ejemplo -" << endl;
    printCuadrado(cuadrados.front());
}
