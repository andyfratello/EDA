#include <iostream>
#include <vector>
using namespace std;

void barra(const vector<int>& v, int n, int m, int i, int sum) {
    if (i == n) cout << sum << endl;
    else {
        if (sum + v[i] <= m/2) barra(v, n, m, i+1, sum + v[i]);
        if (sum - v[i] >= -m/2) barra(v, n, m, i+1, sum - v[i]);
    }
}

int main() {
    int m, n;
    cin >> m >> n;
    vector<int> v(n);
    for (int i = 0; i < n; ++i) cin >> v[i];
    barra(v, n, m, 0, 0);
}
