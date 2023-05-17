#include <iostream>
#include <vector>

using namespace std;

vector<unsigned long int> v;
int n;
int r;
int m;

enum tristate {
    UNDEFINED,
    FALSE,
    TRUE
};

vector<vector<tristate>> cache;

int aModb(long int a, int b) {
	return ((a % b) + b) % b;
}

int aPowbModc(unsigned long int a, int b, int c) { // Hago esto pq sino la potencia se puede ir a un número gigantesco
    if (b == 0) return 1;
    a = aModb(a, c);
    if (b % 2 == 0) {
    	return aPowbModc((a * a) % c, b/2, c) % c;
    }
    else return (a * aPowbModc(a, b-1, c)) % c;
}

bool canReachTarget(int i, unsigned long int prevRes) {
    if (i == n) return prevRes == r;
    if (cache[i][prevRes] != UNDEFINED) return cache[i][prevRes] == TRUE;
    bool res = canReachTarget(i+1, (prevRes + v[i]) % m) ||
    canReachTarget(i+1, (prevRes * v[i]) % m) ||
    canReachTarget(i+1, aPowbModc(prevRes, v[i], m)) ||
    canReachTarget(i+1, aModb(prevRes - v[i], m));
    if (res == true) cache[i][prevRes] = TRUE;
    else cache[i][prevRes] = FALSE;
    return res;
}

int main() {
    int problemNumber = 0;
    cin >> problemNumber;
    while (problemNumber > 0) {
        cin >> n >> r >> m;
        v = vector<unsigned long int>(n);
        for (int i = 0; i < n; i++) {
            cin >> v[i];
        }
        if (r >= m) {
        	cout << "No" << endl;
        	problemNumber++;
        	continue;
        }
        cache = vector<vector<tristate>>(n, vector<tristate>(m, UNDEFINED));
        if (canReachTarget(1, v[0])) cout << "Si" << endl;
        else cout << "No" << endl;
        problemNumber--;
    }

    return 0;
}
