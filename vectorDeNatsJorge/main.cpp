#include <iostream>
#include <vector>

using namespace std;

const vector<int> v = {534, 345,2345,324,623,62345,6544,234,634,534, 345,2345,324,623,62345,6544,234,634,534, 345,2345,324,623,62345,6544,234,634,534, 345,2345,324,623,62345,6544,234,634};
const int n = v.size();
const int r = 3169;
const int m = 3170;

enum tristate {
    UNDEFINED,
    FALSE,
    TRUE
};

unsigned long long int iter = 0;
vector<vector<tristate>> cache(n, vector<tristate>(2*m, UNDEFINED));

long long int aPowbModc(long long int a, int b, int c) { // Hago esto pq sino la potencia se puede ir a un número gigantesco
    long long int res = 1;
    while (b > 0) {
        res = (res * a) % c; // Gracias por tanto profes de Álgebra I :)
        b--;
    }
    return res;
}

bool canReachTarget(int i, long long int prevRes) {
    if (i == n) return prevRes == r;
    if (cache[i][m + prevRes] != UNDEFINED) return cache[i][prevRes] == TRUE;
    bool res = false;
    res = res || canReachTarget(i+1, (prevRes + v[i]) % m);
    res = res || canReachTarget(i+1, (prevRes * v[i]) % m);
    res = res || canReachTarget(i+1, aPowbModc(prevRes, v[i], m));
    res = res || canReachTarget(i+1, (prevRes - v[i]) % m);
    if (res == true) cache[i][m + prevRes] = TRUE;
    else cache[i][m + prevRes] = FALSE;
    return cache[i][m + prevRes] == TRUE;
}

int main() {
    std::cout << canReachTarget(1, v[0]) << std::endl;
    return 0;
}
