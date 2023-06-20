#include <bits/stdc++.h>

using namespace std;

const int INF = 10e7;

#define PRIM 1
#define KRUSKAL 0

vector<vector<int>> capacity;
vector<vector<int>> adj;

int dfs(int s, int t, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    stack<pair<int, int>> S;
    S.emplace(s, INF);

    while (!S.empty()) {
        int cur = S.top().first;
        int flow = S.top().second;
        S.pop();

        for (int next : adj[cur]) {
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == t)
                    return new_flow;
                S.emplace(next, new_flow);
            }
        }
    }
    return 0;
}

int bfs(int s, int t, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INF});

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : adj[cur]) {
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == t)
                    return new_flow;
                q.push({next, new_flow});
            }
        }
    }
    return 0;
}

int maxflow(int s, int t) {
    int flow = 0;
    vector<int> parent(adj.size());
    int new_flow;
    /*
     * usar dfs tiene más sentido en este caso ya que la cota superior de flujo es n.
     * Se cumple que n < m^2.
     */
    while (new_flow = dfs(s, t, parent)) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }
    return flow;
}

int main() {
    // hack para E/S más rápida (sin esto no pasa el juez!)
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n,m;
    cin >> n >> m;
    while (!(m == 0 && n == 0)) {
        adj = vector<vector<int>>(n+2, vector<int>()); // el 0 es s y el n+1 es t
        capacity = vector<vector<int>> (n+2, vector<int>(n+2, -1));
        for (int student = 1; student <= n; student++) {
            int vote;
            cin >> vote;
            if (vote == PRIM) {
                // arista con capacidad 1 de s a los que votaron bien
                adj[0].push_back(student);
                capacity[0][student] = 1;
            } else if (vote == KRUSKAL) {
                // arista de los que toman malas decisiones a t de capacidad también 1
                adj[student].push_back(adj.size()-1);
                capacity[student][adj.size()-1] = 1;
            }
        }
        while (m--) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            capacity[u][v] = 1;
            // las amistades son recíprocas
            adj[v].push_back(u);
            capacity[v][u] = 1;
        }
        /*
         * Se utiliza un algoritmo de flujo máximo (Ford–Fulkerson) para resolver un problema de corte mínimo. Se realiza un corte mínimo en
         * la mínima cantidad de estudiantes disconformes que van a haber dadas la elección de cada uno y las relaciones de amistad que mantienen entre sí.
        */
        cout << maxflow(0, adj.size()-1) << endl;
        cin >> n >> m;
    }
    return 0;
}
