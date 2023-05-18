#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<vector<int>> adj;
vector<bool> visitado;
vector<int> tiempo, low;
int timer;
vector<unsigned int> factorialMemo;

vector<tuple<int, int>> puentes;
unsigned long long int x =0;

void puente(int v, int w) {
    puentes.push_back(make_tuple(v,w));
    puentes.push_back(make_tuple(w,v));
}

// toma un nodo y su padre
void dfs(int u, int p) {
    low[u] = tiempo[u] = ++timer;
    for (int v : adj[u]) {
        if (v == p) continue;
        if (tiempo[v] == 0) { // v no descubierto
            dfs(v, u);
            if (tiempo[u] < low[v]) {
                puente(v, u);
            }
            low[u] = min(low[u], low[v]);
        } else {
            low[u] = min(low[u], tiempo[v]);
        }
    }
}

void hallar_puentes() {
    timer = 0;
    visitado.assign(n+1, false);
    tiempo.assign(n+1, 0);
    low.assign(n+1, -1);
    puentes.clear();
    x=0;
    for (int i=1; i <= n; i++) {
        if (!tiempo[i])
            dfs(i, i);
    }
}

long combinatorio(int i, int k) {
    return factorialMemo[i] / (factorialMemo[k]*factorialMemo[i-k]);
}

void dfsContar(int v, int& count) {
    visitado[v] = true;
    count++;
    for (int w : adj[v]) {
        if (!visitado[w])
            dfsContar(w, count);
    }
}

//double solve() {
float solve() {
    cin >> n >> m;
    int v, w;
    adj.assign(n+1, {});
    for (int i=0; i<m ; i++) {
        cin >> v >> w;
        adj[v].push_back(w);
        adj[w].push_back(v);
    }
    // precalculo los factoriales que voy a necesitar para los combinatorios
    factorialMemo.reserve(n+1);
    factorialMemo[0] = 1;
    for (int i = 1; i <= n; i++) {
        factorialMemo[i] = factorialMemo[i-1] * i;
    }
    hallar_puentes();

    float posibles = combinatorio(n, 2);
    float ganadoras = 0;

    // quitar puentes
    for (auto [v, w] : puentes) {
        for (int i=0; i < adj[v].size(); i++) {
            if (adj[v][i] == w) {
                adj[v].erase(adj[v].begin() + i);
                i--;
            }
        }
    }

    // contar tam de cada componente conexa
    visitado.clear();
    visitado.assign(n, false);
    for (int i=0; i < n; i++) {
        if (!visitado[i]) {
            int count = 0;
            dfsContar(i, count);
            ganadoras += (count > 2 ? combinatorio(count, 2) : 0);
        }
    }

    return (float) ((float) 1 - ganadoras / posibles);
}

int main() {
    float res = solve();
    cout << setprecision(5) << fixed;
    cout << res << endl;
}
