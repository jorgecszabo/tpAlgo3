#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<vector<int>> adj;
vector<vector<int>> adjT;
vector<bool> visitado;
set<int> res;
stack<int> ordenDFS;
vector<int> componenteActual;

void dfsOrden(int v, const vector<vector<int>> &aristas) {
    visitado[v] = true;
    for (int w : aristas[v]) {
        if (!visitado[w])
            dfsOrden(w, aristas);
    }
    ordenDFS.push(v);
}

void dfs(int v, const vector<vector<int>> &aristas) {
    visitado[v] = true;
    componenteActual.push_back(v);
    for (int w : aristas[v]) {
        if (!visitado[w])
            dfs(w, aristas);
    }
}


void dfsDomino(int v, vector<int> &menores, const vector<vector<int>> &aristas) {
    visitado[v] = true;
    for (int w : adj[v]) {
        if (!visitado[w])
            dfsDomino(w, menores, aristas);
        else if (res.count(w) > 0) {
            menores.push_back(w);
        }
    }
}

void solve() {
    cin >> n >> m;
    int v1, v2;
    adj.assign(n+1, {});
    adjT.assign(n+1, {});

    for (int i=0; i<m ; i++) {
        cin >> v1 >> v2;
        adj[v1].push_back(v2);
        adjT[v2].push_back(v2);
    }

    // Algoritmo de Korasaju para encontrar componentes fuertemente conexas
    visitado.assign(n+1, false); // Primer recorrido, deja el stack en orden
    for (int i=1; i<=n; i++)
        if (!visitado[i]) dfsOrden(i, adj);

    vector<int> minDeCadaCFC;
    visitado.assign(n+1, false);
    while (!ordenDFS.empty()) {
        int u = ordenDFS.top();
        if (!visitado[u]) {
            componenteActual.clear();
            dfs(u, adjT); // componente = {v1, ..., vi}
            int raiz = *min_element(componenteActual.begin(), componenteActual.end()); // lineal
            minDeCadaCFC.push_back(raiz);
        }
        ordenDFS.pop();
    }

    // Algoritmo que halla subconjunto minimo de piezas de domino en orden lexicografico
    visitado.assign(n+1, false);
    for (int i : minDeCadaCFC) {
        if (!visitado[i]) {
            vector<int> menores;
            dfsDomino(i, menores, adj);
            // Si encontramos alguno que estaba cubierto lo quitamos
            if (!menores.empty()) {
                for (auto x : menores) res.erase(x);
            }
            res.insert(i);
        }
    }
}

int main() {
    solve();
    cout << res.size() << endl;
    for (auto x : res) cout << x << ' ';
    cout << endl;
}
