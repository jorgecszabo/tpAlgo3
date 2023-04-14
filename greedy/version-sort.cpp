/*
 * Complejidad del algoritmo: O(nLogn)
 */
#include <bits/stdc++.h>
using namespace std;

struct actividad {
    int si, ti, indiceOriginal;
};

bool porSegundaComponente(actividad a, actividad b) {
    return a.ti < b.ti;
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
    // O(nlogn)
    sort(A.begin(), A.end(), porSegundaComponente);
    // Subconjunto S de A con maxima cardinalidad, sin solapamientos. Solo guarda los indices de A que corresponden a cada actividad.
    list<int> S = {};
    // cuando termina ultima actividad.
    int finUltima = -1;
    // O(n)
    for (int i=0; i < n; i++) {
        if (A[i].si  >= finUltima) {
            S.push_back(A[i].indiceOriginal+1);
            finUltima = A[i].ti;
        }
    }
    cout << S.size() << endl;
    for (int act : S) cout << act << " ";
    cout << endl;
}
