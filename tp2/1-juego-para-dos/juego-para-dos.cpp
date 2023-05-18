#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<vector<int>> adj;
vector<bool> visitado;
vector<int> tiempo, low;
int timer;

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
    visitado.assign(n, false);
    tiempo.assign(n, 0);
    low.assign(n+1, -1);
    puentes.clear();
    x=0;
    for (int i=0; i < n; i++) {
        if (!tiempo[i])
            dfs(i, i);
    }
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
    adj.assign(n, {});
    for (int i=0; i<m ; i++) {
        cin >> v >> w;
        v--;
        w--;
        adj[v].push_back(w);
        adj[w].push_back(v);
    }

    hallar_puentes();

    // las posibles jugadas son la arista 1 con la 2, 3, ..., n
    // la arista 2 con la 3, 4, 5, ..., n
    // hasta la arista n-1 con la n
    // es decir Σ (1 <= i < n) i
    float posibles = ((n-1)*(n))/2;

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
    vector<int> tamPorComponente;
    for (int i=0; i < n; i++) {
        if (!visitado[i]) {
            int count = 0;
            dfsContar(i, count);
            tamPorComponente.push_back(count);
        }
    }

    // calcular porbabilidades
    int posiblesJugadasMalas = 0;
    int vertices = n;
    for (auto e : tamPorComponente) {
        posiblesJugadasMalas += e * (vertices - e);
        vertices -= e;
    }

    return (float) ((float) posiblesJugadasMalas / posibles);
}

int main() {
    float res = solve();
    cout << setprecision(5) << fixed;
    cout << res << endl;
    return 0;
}
