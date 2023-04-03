#include <bits/stdc++.h>

using namespace std;

#define N 4
int numeroMagico = (N*N*N + N)/2; // Formula del numero magico
int sumaGlobal = 0;
int llamados = 0;

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

bool esCuadradoMagico(int n, vector<int> cuadrado) {
    // cuadrados.push_back(cuadrado);
    // return true;
    int col = 0;
    int diagDes = 0;
    int diagAsc = 0;

    int primerFila = 0;
    for (int i=0; i < n; i++) primerFila += cuadrado[i];

    int act;
    int filas[n] = {0};

    for (int i=0; i < n; i++) {
        col = 0;
        for (int j=0; j < n; j++) {
            act = cuadrado[i+j*n];
            col += act;
            filas[j] += act;
            if (i == j) diagDes += act;
            if (j == n-i-1) diagAsc += act;
        }
        if (col != primerFila) return false;
    }
    if (diagAsc != primerFila || diagDes != primerFila) return false;
    for (int i=0; i < n; i++) {
        if (filas[i] != primerFila) return false;
    }
    cuadrados.push_back(cuadrado);
    return true;
}

void fuerzaBruta(int n, vector<int> cuadrado, int K) {
    for (int i=1; i <= n*n; i++) {
        if (count(cuadrado.begin(), cuadrado.end(), i) == 0) {
            vector<int> nuevoCuadrado = cuadrado;
            nuevoCuadrado[K] = i;
            if (K == n*n-1) {
                sumaGlobal += esCuadradoMagico(n, nuevoCuadrado);
            } else {
                fuerzaBruta(n, nuevoCuadrado, K+1);
            }
        }
    }
}

int contarCuadradosMagicosFB(int n) {
    vector<int> cuadrado (n*n, 0);
    fuerzaBruta(n, cuadrado, 0);
    return sumaGlobal;
}

void BT_podaMagica(int n, vector<int> cuadrado, int k) {
    llamados++;
    for (int i=1; i <= n*n; i++) {
        if (count(cuadrado.begin(), cuadrado.end(), i) == 0) {
            cuadrado[k] = i;
            int fila = 0;
            int columna = 0;
            int diagAsc = 0;
            int diagDes = 0;
            for (int j=0; j <= k%n; j++) {
                fila += cuadrado[k-j];
            }
            for (int j=0; j < n; j++) {
                columna += cuadrado[k%n + j*n];
            }
            for (int j=0; j < n; j++) {
                diagDes += cuadrado[j*(n+1)];
            }
            if (k == n*n-n) {
                for (int j=0; j < n; j++) {
                    diagAsc += cuadrado[(n-1)*(j+1)];
                }
                if (diagAsc != numeroMagico) {
                    goto jaja;
                }
            }
            if ((k%n == n-1 && fila != numeroMagico) ||
                (k >= (n*n-n) && columna != numeroMagico)) {
                ;
            } else if ( fila <= numeroMagico &&
                        columna <= numeroMagico &&
                        diagAsc <= numeroMagico &&
                        diagDes <= numeroMagico) {
                if (k == n*n-1) {
                    sumaGlobal += esCuadradoMagico(n, cuadrado);

                } else {
                    BT_podaMagica(n, cuadrado, k+1);
                }
            }
            jaja:
            cuadrado[k] = 0;
        }
    }
}

int contarCuadradosMagicos_PODA(int n) {
    vector<int> cuadrado (n*n, 0);
    sumaGlobal = 0;
    BT_podaMagica(n, cuadrado, 0);
    return sumaGlobal;
}



int main() {
    // vector<int> test = {2,7,6,9,5,1,4,0,0};
    // vector<int> test2 = {1,6,8,9,2,3,5,7,4};

    // auto t1 = chrono::high_resolution_clock::now();
    // cout << contarCuadradosMagicosFB(3) << endl;
    auto t2 = chrono::high_resolution_clock::now();
    cout << "cuadrados magicos: " << contarCuadradosMagicos_PODA(N) << endl;
    cout << "llamados: " << llamados << endl;
    auto t3 = chrono::high_resolution_clock::now();
    // cout << "Sin podas tomo: " << chrono::duration_cast<chrono::milliseconds>(t2-t1).count() << "ms" << endl;
    cout << "Con podas tomo: " << chrono::duration_cast<chrono::milliseconds>(t3-t2).count() << "ms" << endl << endl;

    printCuadrado(cuadrados.front());
}