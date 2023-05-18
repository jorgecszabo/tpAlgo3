#include <bits/stdc++.h>

using namespace std;

#define PROCESADO 1
#define EN_PROCESO 2
#define SIN_VISITAR 3

int n, m;
vector<vector<int>> adj;
vector<int> visitado;
vector<tuple<int,int>> aristasCiclo;
stack<int> ordenTopologico;

void ciclo(int u, int v) {
    aristasCiclo.emplace_back(u,v);
}

void dfsCiclos(int v, int p = -1) {
    visitado[v] = EN_PROCESO;
    for (int w : adj[v]) {
        if (w == p) continue;
        if (visitado[w] == SIN_VISITAR)
            dfsCiclos(w, v);
        if (visitado[w] == EN_PROCESO) // Esta arista forma un ciclo
            ciclo(v,w);
    }
    visitado[v] = PROCESADO;
}

void dfsOrden(int v, int p = -1) { // precondición: el grafo no debe tener ciclos
    visitado[v] = EN_PROCESO;
    for (int w : adj[v]) {
        if (w == p) continue;
        if (visitado[w] == SIN_VISITAR)
            dfsOrden(w, v);
    }
    ordenTopologico.push(v);
    visitado[v] = PROCESADO;
}

void dfsComponente(int v, int p = -1) { // precondición: el grafo no debe tener ciclos
    visitado[v] = EN_PROCESO;
    for (int w : adj[v]) {
        if (w == p) continue;
        if (visitado[w] == SIN_VISITAR)
            dfsComponente(w, v);
    }
    visitado[v] = PROCESADO;
}

void solve() {
    cin >> n >> m;
    int v1, v2;
    adj.assign(n, {});
    for (int i=0; i<m ; i++) {
        cin >> v1 >> v2;
        v1--;
        v2--;
        adj[v1].push_back(v2);
    }

    // me guardo las aristas que forman un ciclo en el grafo
    aristasCiclo.clear();
    visitado.assign(n, SIN_VISITAR);
    for (int i = 0; i < n; i++) { // empiezo dfs del vértice 0 para encontrar el camino sin ciclos lexicograficamente más chico
        if (visitado[i] == SIN_VISITAR)
            dfsCiclos(i);
    }
    // elimino los ciclos del grafo
    for (auto [v, w] : aristasCiclo) {
        for (int i=0; i < adj[v].size(); i++) {
            if (adj[v][i] == w) {
                adj[v].erase(adj[v].begin() + i);
                i--;
            }
        }
    }
    // Busco el órden topológico del grafo
    ordenTopologico = stack<int>();
    visitado.assign(n, SIN_VISITAR);
    for (int i = 0; i < n; i++) {
        if (visitado[i] == SIN_VISITAR) {
            dfsOrden(i);
        }
    }
    // busco la cantidad de componentes conexas y a que componente pertenece la pieza que Tuki necesita empujar
    int componente = 0;
    visitado.assign(n, SIN_VISITAR);
    vector<int> res;
    while (!ordenTopologico.empty()) {
        int u = ordenTopologico.top();
        if (visitado[u] == SIN_VISITAR) {
            dfsComponente(u);
            componente++;
            res.push_back(u);
        }
        ordenTopologico.pop();
    }

    // ordeno de menor a mayor e imprimo el resulardo en la consola
    sort(res.begin(), res.end());
    cout << res.size() << endl;
    for (int i = 0; i < res.size()-1; i++) cout << res[i] + 1 << " ";
    cout << res[res.size()-1] + 1 << endl;
}

int main() {
    solve();
    return 0;
}
