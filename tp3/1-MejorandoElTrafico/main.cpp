#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

const unsigned long int INF = 1000*(10e5);

using namespace std;

vector<unsigned long int> dijkstra(const vector<vector<pair<int, int>>> &adj, int x) {
    unsigned int n = adj.size();
    vector<unsigned long int> distance(n+1, INF);
    vector<bool> processed(n+1, false);
    distance[x] = 0;
    priority_queue<pair<long int, int>> q;
    q.emplace(0,x);
    while (!q.empty()) {
        int a = q.top().second;
        q.pop();
        if (processed[a]) continue;
        processed[a] = true;
        for (auto u : adj[a]) {
            int b = u.first; int w = u.second;
            if (distance[a] + w < distance[b]) { // relajación
                distance[b] = distance[a] + w;
                q.emplace(-distance[b],b);
            }
        }
    }
    return distance;
}

int main() {
    int totalCases;
    cin >> totalCases;
    for (int currCase = 1; currCase <= totalCases; currCase++) {
        int n, m, k, s, t;
        cin >> n >> m >> k >> s >> t;
        vector<vector<pair<int,int>>> adj(2*(n+1), vector<pair<int,int>>());
        while (m--) {
            int u, v, w;
            cin >> u >> v >> w;
            adj[u].emplace_back(v, w);
            adj[u+n].emplace_back(v+n, w);
        }
        while (k--) {
            int u, v, w;
            cin >> u >> v >> w;
            adj[u].emplace_back(v+n, w);
        }
        vector<unsigned long int> dist = dijkstra(adj, s);
        cout << ((min(dist[t], dist[t+n]) == INF) ? -1 : min(dist[t], dist[t+n])) << endl;
    }
    return 0;
}
