#include <bits/stdc++.h>

using namespace std;

int N=0; 
int K=0;
int numeroMagico=0;
vector<int> cuadrado;
vector<int> res;

void printCuadrado(vector<int> cua) {
    if (cua.size() == 0) {
        cout << "-1" << endl;
    } else {
        for (int i=0; i < N; i++) {
            for (int j=0; j < N; j++) {
                cout << cua[i*N+j] << " ";
            }
            cout << "\n";
        }
    }
}


inline int cota(int faltan, vector<bool>& usado, int n) {
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

void BT(int n, vector<bool>& usado, int k) {
    if (K==0) return;
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
            int faltanFila        = n - k%n - 1;
            int faltanColumna     = ceil(n - k/n - 1);
            int faltanDiagonalDes = n - ceil(k/(n+1)) - 1;
            int faltanDiagonalAsc = n - ceil(k/(n-1));

            int cotaInfFila    = cota(faltanFila, usado, n);
            int cotaInfCol     = cota(faltanColumna, usado, n);
            int cotaInfDiagAsc = cota(faltanDiagonalAsc, usado, n);
            int cotaInfDiagDes = cota(faltanDiagonalDes, usado, n);

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
            } else if (fila    <= numeroMagico &&
                       columna <= numeroMagico &&
                       diagAsc <= numeroMagico &&
                       diagDes <= numeroMagico) {
                if (k == n*n-1) {
                    //res += 1;
                    //cantidad++;
                    //if (cantidad == X) res.push_back(cuadrado);
                    K--;
                    if (K==0) res = cuadrado;
                } else {
                    //res += BT(n, usado, k+1);
                    BT(n, usado, k+1);
                }
            }
            cuadrado[k] = 0;
            usado[i] = false;
        }
    }
    //return res;
    //return 0;
}

// Encontrar el K esimo cuadrado magico de orden N.
vector<int> cuadradoMagico(int n, int k) {
    numeroMagico = (n*n*n + n)/2; // Formula del numero magico
    N = n;
    K = k;
    cuadrado = vector<int>(N*N, 0);
    vector<bool> usado(N*N+1, false);
    BT(n, usado, 0);
    return res;
}

int main() {
    cin >> N >> K;
    //auto t1 = chrono::high_resolution_clock::now();
    vector<int> resultado = cuadradoMagico(N, K);
    //auto t2 = chrono::high_resolution_clock::now();
    //cout << "Cantidad de cuadrados magicos: " << cantidad << endl;
    //cout << "Llamados recursivos: " << llamados << endl;
    //cout << "Tomo: " << chrono::duration_cast<chrono::milliseconds>(t2-t1).count() << "ms" << endl << endl;
    //cout << "- Res -" << endl;
    //printCuadrado(cuadrados.front());
    printCuadrado(res);
}
