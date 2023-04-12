/* 
 * m<=10^5
 * n<=10^5
 * m*n<=10^7
 */
#include <bits/stdc++.h>
using namespace std;

#define ull unsigned long long

// Donde memo(i, m) -> true/false, para 0 <= i < n, 0 <= m < M(m original)
map<pair<int, int>, bool> memo;

// Esta funcion es necesaria ya que la funcion % de c++ deja el numero en negativo si el original es negativo.
int aModb (ull a, int b) {
    return (a % b + b) % b;
}

bool esEntero(double x) {
    return ceilf(x) == x;
}

float raizN(float radicando, float indice) {
    return pow(radicando, 1/indice);
}

bool solve(int i, ull w, int n, int r, int m, vector<int>& v) {
    if (!esEntero(w)) return false;
    if (i == 0) return (w == 0);
    pair<int, int> par = make_pair(i, w);
   if (memo.count(par) == 0) {
        bool res =  solve(i-1, aModb(w - v[i], m), n, r, m, v) ||   // suma
                    solve(i-1, w / v[i], n, r, m, v) ||             // multiplicacion
                    solve(i-1, raizN(w, v[i]), n, r, m, v) ||       // potenciacion
                    solve(i-1, aModb(w + v[i], m), n, r, m, v);     // resta
        memo.insert(make_pair(par, res));
    }
    return memo.at(par);
}

int main() {
    int c; cin >> c;
    while (c--) {
        memo.clear();
        int n, r, m;
        std::cin >> n >> r >> m;
        vector<int> v(n, 0);
        for (int i=0; i < n; i++) std::cin >> v[i];
        cout << (solve(0, m, n, r, m, v) ? "Si" : "No") << endl;
    }
}
