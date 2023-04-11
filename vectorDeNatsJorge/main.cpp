#include <iostream>
#include <vector>

using namespace std;

int aPowbModc(int a, int b, int c) { // Hago esto pq sino la potencia se puede ir a un número gigantesco
    a = a % c;
    long long int res = 1;
    while (b > 0) {
        res = (res * a) % c; // Gracias por tanto profes de Álgebra I :)
        b--;
    }
    return res;
}

bool canReachTarget(int i, vector<bool> &cachePrev, vector<bool> &cacheCurr, const vector<int> &v, int n, int m , int r) {
    cachePrev[m + (v[i] + v[i+1]) % m] = true;
    cachePrev[m + (v[i] - v[i+1]) % m] = true;
    cachePrev[m + (v[i] * v[i+1]) % m] = true;
    cachePrev[m + aPowbModc(v[i], v[i+1], m)] = true;
    i += 2;
    while (i < n) {
        for (int idx = 0; idx < 2*m; idx++) cacheCurr[idx] = false;
        for (int idx = 0; idx < 2*m; idx++) {
            if (cachePrev[idx]) {
                int prevRes = idx - m; // Para poder representar valores negativos
                cacheCurr[m + ((prevRes + v[i]) % m)] = true;
                cacheCurr[m + ((prevRes - v[i]) % m)] = true;
                cacheCurr[m + ((prevRes * v[i]) % m)] = true;
                cacheCurr[m + aPowbModc(prevRes, v[i], m)] = true;
            }
        }
        swap(cachePrev, cacheCurr); // ES O(1) según la documentación, solo mueve punteros
        i++;
    }
    return cachePrev[m + r];
}

int main() {
    vector<int> v = {4,4,7};
    const int n = v.size();
    int r = 27936; // (4^4^7 mod 100000)
    const int m = 100000;

    vector<bool> cacheCurr(2*m); // Igual me lo limpia el ciclo
    vector<bool> cachePrev(2*m, false);
    std::cout << canReachTarget(0, cachePrev, cacheCurr, v, n, m, r) << std::endl;
    return 0;
}
