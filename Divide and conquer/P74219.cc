#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<int> > Matriu;
const Matriu X({{1, 1}, {1, 0}});

Matriu mult(const Matriu& A, const Matriu& B, int m) {
    Matriu C(2, vector<int>(2, 0));
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < 2; ++k) {
                C[i][j] += A[i][k]*B[k][j];
            }
            C[i][j] %= m;
        }
    }
    return C;
}

void power(const Matriu& X, int n, int m, Matriu& aux) {
    if (n == 1) aux = X;
    else {
        Matriu aux2(2, vector<int>(2));
        power(X, n/2, m, aux2); // matriu X ^ n/2
        aux = mult(aux2, aux2, m);
        if (n%2 != 0) aux = mult(aux, X, m);
    }
}

int fibonacci(int n, int m) {
    if (n < 2) return n;
    Matriu aux(2, vector<int>(2));
    power(X, n, m, aux);
    return aux[0][1];
}

int main() {
    int n, m;
    while (cin >> n >> m) {
        cout << fibonacci(n, m) << endl;
    }
}
