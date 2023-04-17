/*
 * Complejidad del algoritmo: O(nLogn)
 */
#include <bits/stdc++.h>
using namespace std;

struct actividad {
    int si, ti, indiceOriginal;
};

void bucketSortSegundaComponente(int n, vector<actividad> &v) {
    vector<list<actividad>> bucket(2*n); // Buckets de tamaño 1
    for (int i = 0; i < v.size(); i++)
        bucket[v[i].ti - 1].push_back(v[i]);
    int i = 0;
    // O(n) ya que Σ |lista| ∈ bucket = n
    for (list<actividad> &l : bucket)
        for (actividad &a : l) {
            v[i] = a;
            i++;
        }
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
    // O(n)
    bucketSortSegundaComponente(n, A);
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
