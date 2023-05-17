#include <bits/stdc++.h>
using namespace std;

// Datos globales para no tener que recalcular
// Orden N
int N=0; 
// K esimo cuadrado
int K=0;
int numeroMagico=0;
// Almacenar cuadrado actual
vector<vector<int>> cuadrado(0);
vector<vector<int>> resultado;
// Si el numero no se utilizo en el cuadrado, su indice es 0, sino es 1.
vector<bool> usado(0);

// Sumas parciales. Fila, Columna, Diagonal Ascendente, Diagonal Descendente
vector<int> sumF;
vector<int> sumC;
int sumDA;
int sumDD;

// Cantidad de casillas llenadas. Fila, Columna, Diagonal Ascendente, Diagonal Descendente
vector<int> faltanF;
vector<int> faltanC;
int faltanDA;
int faltanDD;

void printMatriz(vector<vector<int>> m) {
    for (int x=0; x < N; x++) {
        for (int y=0; y < N; y++) {
            cout << m[x][y] << " ";
        }
        cout << endl;
    }
}

inline int cota(int faltan) {
    int cota = numeroMagico;
    int y = N*N;
    while (faltan) {
        if (!usado[y]) {
            cota -= y;
            faltan--;
        }
        y--;
    }
    return cota;
}

// Encontrar el K esimo cuadrado magico de orden N.
// Utiliza variables globales
void hallarCuadrado(int i, int j) {
    for (int nuevo=1; nuevo <= N*N; nuevo++) {
        if (!usado[nuevo]) {
            // Hago todos los calculos asumiendo que ya coloque el numero.
            cuadrado[i][j] = nuevo;
            usado[nuevo] = true;
            // Sumar nuevo numero a fila, columna y diagonales
            sumF[i] += nuevo;
            sumC[j] += nuevo;
            sumDD += (i == j) ? nuevo : 0;
            sumDA += (i == N-1-j) ? nuevo : 0;
            
            // Cuantos numeros faltan agregar a la fila/columna/diagonal para completarla
            faltanF[i]--;
            faltanC[j]--;
            faltanDD -= (i == j);
            faltanDA -= (i == N-1-j);
            
            // Aprovechamos la logica de circuito de C++ para no tener que calcular las ultimas cotas si no es necesario.
            bool podo =
                // Si alguna fila, columna o diagonal completa suma distinto al numero numagico
                // Si alguna fila, columna o diagonal parcial suma mas o igual al numero magico
                (j+1==N &&           sumF[i] != numeroMagico) ||
                (i+1< N &&           sumC[j] >= numeroMagico) ||
                (i+1==N &&           sumC[j] != numeroMagico) ||
                (i+1==N &&           sumDA   != numeroMagico) ||
                (i+1< N &&           sumDA   >= numeroMagico) ||
                (j+1< N &&           sumF[i] >= numeroMagico) ||
                (i+1< N && j+1<N &&  sumDD   >= numeroMagico) ||
                (i+1==N && j+1==N && sumDD   != numeroMagico) ||
                // Solo aplico la poda por cotas inferiores cuando las otras fallan por que cuesta mas.
                // Si alguna suma parcial es menor al minimo necesario para poder sumar el numero magico dados los numeros que no estan usados.
                (sumC[j] < cota(faltanC[j]))                  ||
                (sumDD   < cota(faltanDD))                    ||            
                (sumF[i] < cota(faltanF[i]))                  ||
                (sumDA   < cota(faltanDA));

            // Si llegamos al ultimo lugar, encontramos un cuadrado magico. Debido a que podamos todos los cuadrados completos que no son magicos.
            if (i+1 == N && j+1 == N && !podo) { 
                K--;
                // Si es el K esimo, lo guardamos
                if(K==0) resultado = cuadrado;
            }

            // Si todavia no llegue al cuadrado magico que busco y no pode la rama actual
            if (K > 0 && !podo) {
                hallarCuadrado(i + (j+1==N), (j+1==N) ? 0 : j+1);
            }

            // Backtrack: revertir al estado anterior del cuadrado sin el numero nuevo.
            cuadrado[i][j] = 0;
            usado[nuevo] = false;
            sumF[i] -= nuevo;
            sumC[j] -= nuevo;
            sumDD -= (i == j) ? nuevo : 0;
            sumDA -= (i == N-1-j) ? nuevo : 0;
            faltanF[i]++;
            faltanC[j]++;
            faltanDD += (i == j);
            faltanDA += (i == N-1-j);
        }
    }
}

// Encontrar el K esimo cuadrado magico de orden N.
void solve() {
    // Formula del numero magico
    numeroMagico = (int) (N*N*N + N)/2;           
    cuadrado = vector<vector<int>>(N, vector<int>(N,0));
    usado = vector<bool>(N*N+1, false);

    // Inicializar sumas auxiliares
    sumF = vector<int>(N, 0);
    sumC = vector<int>(N, 0);
    sumDA = 0;
    sumDD = 0;

    faltanF = vector<int>(N, N);
    faltanC = vector<int>(N, N);
    faltanDA = N;
    faltanDD = N;

    hallarCuadrado(0,0);
}

int main() {
    std::cin >> N >> K;
    solve();
    // No encontro
    if (resultado.size() == 0) cout << -1 << endl;
    // Encontro
    else printMatriz(resultado);
}
