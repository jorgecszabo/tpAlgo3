#include <bits/stdc++.h>
using namespace std;

enum tristate {
    UNDEFINED,
    FALSE,
    TRUE
};

bool esEntero(float x) {
    return ceilf(x) == x;
}

float raizN(float radicando, float indice) {
    return pow(radicando, 1/indice);
}

vector<int> v = {3,1,5,2,1};
map<pair<int, int>, bool> memo;

bool solve(int i, float w, vector<int>& v) {
    if (!esEntero(w)) return false;
    if (i == 0) return (w - v[i]) == 0;
    pair<int, int> par = make_pair(i, w);
    if (memo.count(par) == 0) {
        bool res = solve(i-1, w - v[i], v) || solve(i-1, w / v[i], v) || solve(i-1, raizN(w, v[i]), v);
        memo.insert(make_pair(par, res));
    }
    return memo.at(par);
    //return solve(i-1, w - v[i], v) || solve(i-1, w / v[i], v) || solve(i-1, raizN(w, v[i]), v);
}

int main() {
    int w = 400;
    cout << "got:      " << (solve(v.size()-1, w, v) ? "true" : "false") << endl;
    cout << "expected: true" << endl;
    vector<int> a = {4,5};
    int b = 21;
    cout << "got:      " << (solve(a.size()-1, b, a) ? "true" : "false") << endl;
    cout << "expected: false" << endl;
}
