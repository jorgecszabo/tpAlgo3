#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<vector<int>> adj;
vector<vector<int>> adjT;
vector<vector<int>> condensado;
vector<bool> visitado;

set<int> res;

vector<int> S;
vector<int> componente;

void dfs1(int v) {
    visitado[v] = true;
    for (int w : adj[v]) {
        if (!visitado[w])
            dfs1(w);
    }
    S.push_back(v);
}

void dfs2(int v) {
    visitado[v] = true;
    componente.push_back(v);

    for (int w : adjT[v]) {
        if (!visitado[w])
            dfs2(w);
    }
}


void dfsDomino(int v, vector<int> &menores) {
    visitado[v] = true;
    for (int w : condensado[v]) {
        if (!visitado[w])
            dfsDomino(w, menores);
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
    condensado.assign(n+1, {});

    for (int i=0; i<m ; i++) {
        cin >> v1 >> v2;
        adj[v1].push_back(v2);
        adjT[v2].push_back(v2);
    }

    // Algoritmo de Korasaju para encontrar componentes fuertemente conexas
    visitado.assign(n+1, false); // Primer recorrido, deja S con los ordenes
    for (int i=1; i<=n; i++)
         if (!visitado[i]) dfs1(i);

    vector<int> raices(n+1);
    vector<int> nodos_r;

    reverse(S.begin(), S.end());
    visitado.assign(n+1, false);
    for (int i : S) {
         if (!visitado[i]) {
            dfs2(i); // componente = {v1, ..., vi}
            
            int raiz = *min_element(componente.begin(), componente.end()); // lineal
            for (int a : componente) {
                raices[a] = raiz;
            }
            nodos_r.push_back(raiz);

            componente.clear();
        }
    }

    // Condensar el grafo original
    for (int i=1; i < n; i++) {
        for (int j : adj[i]) {
            int i_r = raices[i];
            int j_r = raices[j];
            if (i_r != j_r) // si la raiz de j no pertenece a la componente conexa actual
                condensado[i_r].push_back(j_r);
        }
    }

    // Algoritmo que halla subconjunto minimo de piezas de domino en orden lexicografico
    visitado.assign(n+1, false);
    for (int i : nodos_r) {
         if (!visitado[i]) {
            vector<int> menores;
            dfsDomino(i, menores);
            // Si encontramos alguno que estaba cubierto lo quitamos
            if (menores.size() != 0) {
                for (auto x : menores) res.erase(x);
                res.insert(i);
            } else {
                res.insert(i);
            }
         }
    }
}

int main() {
    solve();
    cout << res.size() << endl;
    for (auto x : res) cout << x << ' ';
    cout << endl;
}
