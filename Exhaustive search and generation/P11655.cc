#include <iostream>
#include <vector>
using namespace std;

void write(const vector<int>& sol, const vector<bool>& vis, int n) {
    cout << '{';
    bool first = true;
    for (int i = 0; i < n; ++i) {
        if (vis[i]) {
            if (first) first = false;
            else cout << ',';
            cout << sol[i];
        }
    }
    cout << '}' << endl;
}

void sumes(vector<int>& sol, vector<bool>& vis, int n, int s, int sum_resto, int i, int sum_actual) {
    if (i == n) {
        if (s == sum_actual) write(sol, vis, n);
    } else {
        if (sum_actual + sum_resto - sol[i] >= s) {
            vis[i] = false;
            sumes(sol, vis, n, s, sum_resto - sol[i], i+1, sum_actual);
        }
        if (sum_actual + sol[i] <= s) {
            vis[i] = true;
            sumes(sol, vis, n, s, sum_resto - sol[i], i+1, sum_actual + sol[i]);
        }
    }
}

int main() {
    int s, n;
    cin >> s >> n;
    vector<int> sol(n);
    int suma = 0;
    for (int i = 0; i < n; ++i) {
        cin >> sol[i];
        suma += sol[i];
    }
    vector<bool> vis(n, false);
    sumes(sol, vis, n, s, suma, 0, 0);
}
