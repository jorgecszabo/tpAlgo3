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


// Fuente: https://www.geeksforgeeks.org/linked-list-representation-disjoint-set-data-structures/
struct Item;
 
// to represent Node of linked list. Every
// node has a pointer to representative
struct Node
{
    int val;
    Node *next;
    Item *itemPtr;
};
 
// A list has a pointer to head and tail
struct Item
{
    Node *hd, *tl;
};
 
// To represent union set
class ListSet
{
private:
 
    // Hash to store addresses of set representatives
    // for given values. It is made global for ease of
    // implementation. And second part of hash is actually
    // address of Nodes. We typecast addresses to long
    // before storing them.
    unordered_map<int, Node *> nodeAddress;
 
public:
    void makeset(int a);
    Item* find(int key);
    void Union(Item *i1, Item *i2);
};
 
// To make a set with one object
// with its representative
void ListSet::makeset(int a)
{
    // Create a new Set
    Item *newSet = new Item;
 
    // Create a new linked list node
    // to store given key
    newSet->hd = new Node;
 
    // Initialize head and tail
    newSet->tl = newSet->hd;
    nodeAddress[a] = newSet->hd;
 
    // Create a new set
    newSet->hd->val = a;
    newSet->hd->itemPtr = newSet;
    newSet->hd->next = NULL;
}
 
// To find representative address of a
// key
Item *ListSet::find(int key)
{
    Node *ptr = nodeAddress[key];
    return (ptr->itemPtr);
}
 
// union function for joining two subsets
// of a universe. Merges set2 into set1
// and deletes set1.
void ListSet::Union(Item *set1, Item *set2)
{
    Node *cur = set2->hd;
    while (cur != 0)
    {
        cur->itemPtr = set1;
        cur = cur->next;
    }
 
    // Join the tail of the set to head
    // of the input set
    (set1->tl)->next = set2->hd;
    set1->tl = set2->tl;
 
    delete set2;
}

tuple<double, double> solve(vector<tuple<int,int,double>> &listaAristas, int n, int cantModem, int costoUTP, double limitUTP, int costoFibra) {
    sort(listaAristas.begin(),listaAristas.end(), tercerElemento);
    int tamBosque = n;
    double acumUTP = 0;
    double acumFibra = 0;

    ListSet dsu;
    for (int i=0; i < n; i++) {
        dsu.makeset(i);
    }

    for(auto [u, v, d] : listaAristas){
        //si (u,v) es arista segura
        if(dsu.find(u) != dsu.find(v)){
            dsu.Union(dsu.find(u),dsu.find(v));
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
    output_file.open("runtime-data/runtime-linked-list.csv", std::ios_base::out);
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


