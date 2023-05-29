#include <bits/stdc++.h>

using namespace std;
using ll = long long;
const ll inf = 1e18;

double distancia(const tuple<int, int> &p1, const tuple<int, int> &p2) { // <x,y>
    return sqrt((get<0>(p2)-get<0>(p1))*(get<0>(p2)-get<0>(p1)) + (get<1>(p2)-get<1>(p1))*(get<1>(p2)-get<1>(p1)));
}

bool tercerElemento(const tuple<int, int, double>& a,
                    const tuple<int, int, double>& b) {
    return (get<2>(a) < get<2>(b));
}

struct DSU{

    DSU(int n){
        padre = rank = vector<int>(n);
        for(int v = 0; v < n; v++) padre[v] = v;
    }

    int find(int v){
        if(v == padre[v]) return v;
        return padre[v] = find(padre[v]);
    }

    void unite(int u, int v){
        u = find(u), v = find(v);
        if(u == v) return;
        if(rank[u] < rank[v]) swap(u,v);
        padre[v] = padre[u];
        rank[u] = max(rank[u],rank[v]+1);
    }

    vector<int> padre;
    vector<int> rank;
};

tuple<double, double> solve(vector<tuple<int,int,double>> &listaAristas, int n, int cantModem, int costoUTP, double limitUTP, int costoFibra) {
    sort(listaAristas.begin(),listaAristas.end(), tercerElemento);
    int tamBosque = n;
    double acumUTP = 0;
    double acumFibra = 0;
    DSU dsu(n);
    for(auto [u, v, d] : listaAristas){
        //si (u,v) es arista segura
        if(dsu.find(u) != dsu.find(v)){
            dsu.unite(u,v);
            tamBosque--;
            if (d > limitUTP) {
                acumFibra += d * costoFibra;
            } else {
                acumUTP += d * costoUTP;
            }
        }
        if (tamBosque == cantModem) break;
    }
    return make_tuple(acumUTP, acumFibra);
}

int main() {
    auto repeticiones = 25;
    chrono::high_resolution_clock c;
    ofstream output_file;
    output_file.open("runtime-data/runtime-rank-y-compression.csv", std::ios_base::out);
    output_file << "n,time" << endl;

    int casos;
    cin >> casos;
    for (int caso = 1; caso <= casos; caso++) {
        int n, limitUTP, cantModems, precioUTP, precioFibra;
        cin >> n >> limitUTP >> cantModems >> precioUTP >> precioFibra;
        int input = n;
        vector<tuple<int,int>> oficinas;
        vector<tuple<int,int,double>> listaAdj; // <u, v, peso>
        while (input--) {
            int x, y;
            cin >> x >> y;
            oficinas.emplace_back(x,y);
        }

        // genero la lista de adyacencias del grafo pesado. Va a ser un grafo completo.
        for (int i = 0; i < oficinas.size() - 1; i++) {
            for (int j = i + 1; j < oficinas.size(); j++) {
                listaAdj.emplace_back(i, j, distancia(oficinas[i], oficinas[j]));
                listaAdj.emplace_back(j, i, distancia(oficinas[i], oficinas[j]));
            }
        }

        double contador=0;
        tuple<double, double> res;
        for (auto i=0; i < repeticiones; i++) {
            auto t1 = c.now();
            res = solve(listaAdj, n, cantModems, precioUTP, limitUTP, precioFibra);
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
