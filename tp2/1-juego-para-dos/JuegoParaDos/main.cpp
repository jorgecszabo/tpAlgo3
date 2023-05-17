#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;
#define NO_VISITADO 0
#define EN_PROCESO 1
#define PROCESADO 2

vector<vector<int>> aristas;
vector<int> visitado;
vector<int> backEdgesConExtremoInferiorEn;
vector<int> backEdgesConExtremoSuperiorEn;
vector<int> cubrenMemo;
vector<vector<int>> tree;

int cubren(int v, int p = -1) {
    if (cubrenMemo[v] != -1) return cubrenMemo[v];
    int res = backEdgesConExtremoInferiorEn[v] - backEdgesConExtremoSuperiorEn[v];
    for (int hijo : tree[v])
        if (hijo != p) res += cubren(hijo, v);
    return cubrenMemo[v] = res;
}

void dfs(int v, int p = -1) {
    visitado[v] = EN_PROCESO;
    for (int u : aristas[v]) {
        if (visitado[u] == NO_VISITADO) {
            tree[v].push_back(u);
            dfs(u, v);
        }
        else if (u != p) {
            backEdgesConExtremoSuperiorEn[u]++;
            backEdgesConExtremoInferiorEn[v]++;
        }
    }
    visitado[v] = PROCESADO;
}

int main() {
    int n, m;
    cin >> n >> m;
    aristas = vector<vector<int>>(n, vector<int>());
    visitado = vector<int>(n, NO_VISITADO);
    backEdgesConExtremoInferiorEn = vector<int>(n,0);
    backEdgesConExtremoSuperiorEn = vector<int>(n,0);
    cubrenMemo = vector<int>(n, -1);
    tree = vector<vector<int>>(n, vector<int>());
    int inputSize = m;
    while (inputSize--) {
        int u, v;
        cin >> u >> v;
        // Nosotros vamos a contar los nodos desde el 0 para más facilidad
        u--;
        v--;
        aristas[u].push_back(v);
        aristas[v].push_back(u);
    }

    double componentes = 0.0;
    for (int i = 0; i < n; i++) {
        if (visitado[i] == NO_VISITADO) {
            componentes++;
            dfs(i);
        }
    }

    double puentes = 0.0;
    for (int i = 0; i < n; i++) {
        if (cubren(i) == 0) puentes++;
    }

    vector<vector<int>> aarrbol = tree;

    puentes -= componentes;
    cout << fixed << showpoint << setprecision(5) << puentes << endl;
    return 0;
}
