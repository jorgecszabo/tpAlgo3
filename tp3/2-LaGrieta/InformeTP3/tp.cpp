#include <bits/stdc++.h>

const long long int INF = 1000*(10e6);

using namespace std;

vector<long long int> dijkstra(const vector<vector<pair<int, int>>> &adj, int x) {
    unsigned int n = adj.size();
    vector<long long int> distance(n+1, INF);
    vector<bool> processed(n+1, false);
    distance[x] = 0;
    priority_queue<pair<long long int, int>> q;
    q.emplace(0,x);
    while (!q.empty()) {
        int a = q.top().second;
        q.pop();
        if (processed[a]) continue;
        processed[a] = true;
        for (auto const &u : adj[a]) {
            int b = u.first; int w = u.second;
            if (distance[a] + w < distance[b]) { // relajación
                distance[b] = distance[a] + w;
                q.emplace(-distance[b],b); // para usar una max queue como si fuera una min queue
            }
        }
    }
    return distance;
}

/*
vector<long long int> evilDijkstra(const vector<vector<pair<int, int>>> &adj, int x) {
    unsigned int n = adj.size();
    vector<long long int> distance(n+1, INF);
    vector<bool> processed(n+1, false);
    distance[x] = 0;
    list<pair<long long int, int>> q;
    q.emplace_back(0,x);
    while (!q.empty()) {
        q.sort();
        int a = q.front().second;
        q.pop_front();
        if (processed[a]) continue;
        processed[a] = true;
        for (auto const &u : adj[a]) {
            int b = u.first; int w = u.second;
            if (distance[a] + w < distance[b]) { // relajación
                distance[b] = distance[a] + w;
                q.emplace_back(distance[b],b); // para usar una max queue como si fuera una min queue
            }
        }
    }
    return distance;
}*/


// O(n**2)
vector<long long int> evilDijkstra(const vector<vector<pair<int, int>>> &adj, int x) {
    unsigned int n = adj.size();
    vector<long long int> distance(n+1, INF);
    vector<bool> processed(n+1, false);
    distance[x] = 0;
    vector<pair<long long int, int>> v;
    v.emplace_back(0,x);
    while (!v.empty()) {
        auto asd = min_element(v.begin(), v.end());
        int a = (*asd).second;
        v.erase(asd);
        if (processed[a]) continue;
        processed[a] = true;
        for (auto const &u : adj[a]) {
            int b = u.first; int w = u.second;
            if (distance[a] + w < distance[b]) { // relajación
                distance[b] = distance[a] + w;
                v.emplace_back(distance[b],b); // para usar una max queue como si fuera una min queue
            }
        }
    }
    return distance;
}
/*
vector<long long int> evilDijkstra(const vector<vector<pair<int, int>>> &adj, int x) {
    unsigned int n = adj.size();
    vector<long long int> distance(n+1, INF);
    vector<bool> processed(n+1, false);
    distance[x] = 0;
    list<pair<long long int, int>> q;
    q.emplace_back(0,x);
    while (!q.empty()) {
        auto asd = 
        int a = q.front().second;
        q.pop_front();
        if (processed[a]) continue;
        processed[a] = true;
        for (auto const &u : adj[a]) {
            int b = u.first; int w = u.second;
            if (distance[a] + w < distance[b]) { // relajación
                distance[b] = distance[a] + w;
                q.emplace_back(distance[b],b); // para usar una max queue como si fuera una min queue
            }
        }
    }
    return distance;
}*/

int main() {
    auto repeticiones = 25;
    chrono::high_resolution_clock c;
    ofstream output_file;
    output_file.open("ralos.csv", std::ios_base::out);

    int totalCases;
    cin >> totalCases;
    for (int currCase = 1; currCase <= totalCases; currCase++) {
        int n, m, k, s, t;
        cin >> n >> m >> k >> s >> t;
        
        vector<vector<pair<int,int>>> adj(2*(n+1), vector<pair<int,int>>());
        int mprime = m;
        while (mprime--) {
            int u, v, w;
            cin >> u >> v >> w;
            adj[u].emplace_back(v, w);
            adj[u+n].emplace_back(v+n,w);
        }
        int kprime = k;
        while (kprime--) {
            int u, v, w;
            cin >> u >> v >> w;
            adj[u].emplace_back(v+n, w);
            adj[v].emplace_back(u+n, w);
        }
        vector<long long int> dist;
        double avgTime = 0.0;
        for (int i = 1; i <= repeticiones; i++) {
            auto t1 = c.now();
            dist = evilDijkstra(adj, s);
            auto t2 = c.now();
            auto duracion = chrono::duration<double>(t2 - t1).count();
            avgTime += duracion;
        }
        avgTime = avgTime / repeticiones;
        output_file << n << "," << m << "," << k << "," << s << "," << t << "," << avgTime << endl;
        cout << ((min(dist[t], dist[t+n]) == INF) ? -1 : min(dist[t], dist[t+n])) << endl;
    }
    output_file.close();
    return 0;
}
