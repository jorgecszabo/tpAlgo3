#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<vector<int>> adj;
vector<vector<int>> adjT;
vector<int> verticesEnComponente;
vector<bool> visitado;
stack<int> ordenDFS;

void dfsOrden(const vector<vector<int>> &aristas, int v) {
    visitado[v] = true;
    for (int w : adj[v]) {
        if (!visitado[w])
            dfsOrden(aristas, w);
    }
    ordenDFS.push(v);
}

void dfsComponente(const vector<vector<int>> &aristas, int v) {
    visitado[v] = true;
    for (int w : aristas[v]) {
        if (!visitado[w])
            dfsComponente(aristas, w);
    }
    verticesEnComponente.push_back(v);
}

void solve() {
    cin >> n >> m;
    int v1, v2;
    adj.assign(n, {});
    adjT.assign(n,{});
    for (int i=0; i<m ; i++) {
        cin >> v1 >> v2;
        v1--;
        v2--;
        adj[v1].push_back(v2);
        adjT[v2].push_back(v1);
    }

    // Busco el órden en el que termina dfs para cada vertice
    // No es exactamente el órden topológico porque el grafo puede tener ciclos
    visitado.assign(n, false);
    for (int i = 0; i < n; i++) {
        if (!visitado[i]) {
            dfsOrden(adj, i);
        }
    }

    // Para aplicar Kosaraju corro dfs en el órden anteriormente calculado sobre el grafo traspuesto.
    visitado.assign(n, false);
    vector<int> minimoDeCFC(n);
    while (!ordenDFS.empty()) {
        int u = ordenDFS.top();
        if (!visitado[u]) {
            verticesEnComponente.clear();
            dfsComponente(adjT, u);
            int min = *min_element(verticesEnComponente.begin(), verticesEnComponente.end());
            for (int v : verticesEnComponente) {
                minimoDeCFC[v] = min;
            }
        }
        ordenDFS.pop();
    }
    // Usando minimoDeCFC quiero condensar mi digrafo original en un dag donde
    // cada cfc es representada por el vertice de menor orden lexicográfico pertenteciente a esta
    vector<vector<int>> grafoCondensado(n, vector<int>());
    // Uso la misma estructura que el grafo original para no tener que mapear un numero de vertice a otro de un grafo con menos vertices.
    // Si un vértice no está en el grafo consensado, simplemente lo ignoro.
    vector<bool> enGrafoCondensado(n, false);
    for (int e : minimoDeCFC) enGrafoCondensado[e] = true;
    for (int v = 0; v < n; v++) {
        for (int u : adj[v]) {
            if (minimoDeCFC[v] != minimoDeCFC[u]) // es decir que no pertenecen a la misma cfc pero están unidas en el digrafo original
                grafoCondensado[minimoDeCFC[v]].push_back(minimoDeCFC[u]);
        }
    }
    // Ahora, los vértices en este grafo condensado con grado de entrada 0 son los que Tuki debe empujar
    vector<int> gradoDeEntrada(n, 0);
    vector<int> res;
    for (int u = 0; u < n; u++) { // Notar que los vértices se recorren en órden y se agregan en órden al vector res
        if (!enGrafoCondensado[u]) continue;
        for (int v : grafoCondensado[u]) {
            gradoDeEntrada[v]++; // arista u --> v
        }
    }

    for (int u = 0; u < n; u++)
        if (gradoDeEntrada[u] == 0 && enGrafoCondensado[u]) res.push_back(u);

    // imprimo el resulardo en la consola
    cout << res.size() << endl;
    for (auto e : res) cout << e + 1 << " ";
    cout << endl;
}

int main() {
    solve();
    return 0;
}
