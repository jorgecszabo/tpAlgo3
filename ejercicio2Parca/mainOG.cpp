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
int aModb (int a, int b) {
    return (a % b + b) % b;
}

ull aPowbModc(ull a, int b, int c) { // Hago esto pq sino la potencia se puede ir a un número gigantesco
    a = aModb(a,c);
    ull res = pow(a,b);
    res = aModb(res, c);
    return res;
    /*ull res = 1;
    while (b > 0) {
        res = (res * a) % c; // Gracias por tanto profes de Álgebra I :)
        b--;
    }
    return res;
    */
}

bool solve(int i, ull w, int n, int r, int m, vector<int>& v) {
    if (i == n) return (aModb(w,m) == r);
    pair<int, int> par = make_pair(i, w);
    if (memo.count(par) == 0) {
        bool res =  solve(i+1, aModb(w - v[i], m), n, r, m, v) ||
                    solve(i+1, w * v[i], n, r, m, v) ||
                    solve(i+1, aPowbModc(w, v[i], m), n, r, m, v) ||
                    solve(i+1, w + v[i], n, r, m, v);
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
        cout << (solve(0, 0, n, r, m, v) ? "Si" : "No") << endl;
    }
}
