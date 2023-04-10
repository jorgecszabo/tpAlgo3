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

int aPowbModc(int a, int b, int c) {
    long long int res = 1;
    a = a % c;
    while (b > 0) {
        res = (res * a) % c; // Consultar apunte Álgebra I :)
        b--;
    }
    return res;
}

bool canReachTarget(int i, int prevRes) {
    if (i == n) return prevRes == r;
    if (cache[i][m + prevRes] != UNDEFINED) return cache[i][m + prevRes] == TRUE;
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
