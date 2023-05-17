/*
 * Complejidad del algoritmo: O(n)
 */
#include <bits/stdc++.h>
using namespace std;

struct actividad {
    int si, ti, indiceOriginal;
};

bool porSegundaComponente(actividad a, actividad b) {
    return a.ti > b.ti; // Para que sea un min heap
}

int main() {
    int n; cin >> n;
    // Conjunto de actividades
    vector<actividad> A(n);
    for (int i=0; i < n; i++) {
        actividad ai;
        cin >> ai.si >> ai.ti;
        ai.indiceOriginal = i;
        A[i] = ai;
    }

    // algoritmo de floyd, contruye un min heap de A ordenado por los tiempos que termina cada actividad
    // O(n) (algo2 y https://en.cppreference.com/w/cpp/algorithm/make_heap )
    make_heap(A.begin(), A.end(), porSegundaComponente);
    // Subconjunto S de A con maxima cardinalidad, sin solapamientos. Solo guarda los indices de A que corresponden a cada actividad.
    list<int> S = {};
    // cuando termina ultima actividad.
    int finUltima = -1;
    // O(n)
    for (int i=0; i < n; i++) {
        actividad ai = A.front();
        if (ai.si  >= finUltima) {
            S.push_back(ai.indiceOriginal+1);
            finUltima = ai.ti;
        }
        pop_heap(A.begin(), A.end(), porSegundaComponente); A.pop_back(); // Queda la siguiente actividad que termina antes que las otras.
    }
    cout << S.size() << endl;
    for (int act : S) cout << act << " ";
    cout << endl;
}
