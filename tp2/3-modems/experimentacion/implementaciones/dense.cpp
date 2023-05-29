// Fuente: https://fedelebron.com/static/kruskal_dense.cpp
#include <bits/stdc++.h>


using namespace std;
using ll = long long;
const ll inf = 1e18;

#define forn(i, n) for(int i = 0; i < (n); ++i)
#define INFINITY 9999999

using std::make_pair;
using std::min;
using std::pair;
using std::vector;
using std::chrono::high_resolution_clock;
using std::chrono::milliseconds;
using std::chrono::duration_cast;

typedef double cost_t;
typedef vector<cost_t> vcost_t;
typedef vector<vcost_t> vvcost_t;
typedef vvcost_t adjacency_matrix;
typedef vector<int> vint;
typedef pair<int, int> edge;
typedef vector<bool> vbool;
typedef pair<cost_t, edge> weighted_edge;

void initialize(const adjacency_matrix& A,
                vcost_t& dist) {
  int n = dist.size();
  forn(i, n) {
    forn(j, n) {
      dist[i] = min(dist[i], A[i][j]);
    }
  }
}

__attribute__((always_inline)) weighted_edge lightest_edge(const adjacency_matrix& A,
                            const vcost_t& dist,
                            const vbool& rep) {
  int idx = 0, n = dist.size();
  while (!rep[idx]) ++idx;
  for (int i = idx + 1; i < n; ++i) {
    if (!rep[i]) continue;
    if (dist[i] < dist[idx]) idx = i;
  }
  cost_t weight = dist[idx];
  int target = 0;
  for (int i = 0; i < n; ++i) {
    if (!rep[i]) continue;
    if (A[idx][i] == weight) {
      target = i;
      break;
    }
  }

  return weighted_edge(weight, edge(idx, target));
}

__attribute__((always_inline)) void contract(const weighted_edge& e,
              adjacency_matrix& A,
              vcost_t& dist,
              vbool& rep) {
  int n = dist.size(),
      u = e.second.first, // new parent
      v = e.second.second; // new child
  rep[v] = false;
  dist[u] = INFINITY;
  for (int i = 0; i < n; ++i) {
    if (!rep[i]) continue;
    if (i == u) continue;
    A[i][u] = A[u][i] = min(A[u][i], A[v][i]);
    dist[u] = min(dist[u], A[u][i]);
  }
}

double distancia(const tuple<int, int> &p1, const tuple<int, int> &p2) { // <x,y>
    return sqrt((get<0>(p2)-get<0>(p1))*(get<0>(p2)-get<0>(p1)) + (get<1>(p2)-get<1>(p1))*(get<1>(p2)-get<1>(p1)));
}

bool tercerElemento(const tuple<int, int, double>& a,
                    const tuple<int, int, double>& b) {
    return (get<2>(a) < get<2>(b));
}

tuple<double, double> solve(adjacency_matrix &matrizAdj, int n, int cantModem, int costoUTP, double limitUTP, int costoFibra) {
    int tamBosque = matrizAdj.size();
    cost_t total_cost = 0;
    vcost_t dist(n, INFINITY);
    vbool rep(n, true);

    double acumUTP = 0;
    double acumFibra = 0;

    initialize(matrizAdj, dist);

    int remaining = n - 1;
    while (remaining-- > 0) {
        weighted_edge e = lightest_edge(matrizAdj, dist, rep);
        total_cost += e.first;
        contract(e, matrizAdj, dist, rep);
        tamBosque--;
        double d = get<0>(e);
        if (d > limitUTP) {
            acumFibra += d * costoFibra;
        } else {
            acumUTP   += d * costoUTP;
        }
        if (tamBosque == cantModem) break;
    }
    return make_tuple(acumUTP, acumFibra);
}


int main() {
    auto repeticiones = 25;
    chrono::high_resolution_clock c;
    ofstream output_file;
    output_file.open("runtime-data/runtime-dense.csv", std::ios_base::out);
    output_file << "n,time" << endl;

    int casos;
    cin >> casos;
    for (int caso = 1; caso <= casos; caso++) {
        int n, limitUTP, cantModems, precioUTP, precioFibra;
        cin >> n >> limitUTP >> cantModems >> precioUTP >> precioFibra;
        int input = n;
        vector<tuple<int,int>> oficinas;
        adjacency_matrix matrizAdj(n, vcost_t(n, INFINITY));
        while (input--) {
            int x, y;
            cin >> x >> y;
            oficinas.emplace_back(x,y);
        }

        // genero la lista de adyacencias del grafo pesado. Va a ser un grafo completo.
        for (int i = 0; i < oficinas.size() - 1; i++) {
            for (int j = i + 1; j < oficinas.size(); j++) {
                matrizAdj[i][j] = matrizAdj[j][i] = distancia(oficinas[i], oficinas[j]);
            }
        }

        double contador=0;
        tuple<double, double> res;
        for (auto i=0; i < repeticiones; i++) {
            auto t1 = c.now();
            res = solve(matrizAdj, n, cantModems, precioUTP, limitUTP, precioFibra);
            auto t2 = c.now();
            auto duracion = chrono::duration<double>(t2 - t1).count();
            contador += duracion;
        }
        output_file << n << "," << contador / repeticiones << endl;
        
        cout << setprecision(3) << fixed;
        cout << "Caso #" << caso << ": ";
        cout << get<0>(res) << " " << get<1>(res) << endl;
    }
    output_file.close();
    return 0;
}
