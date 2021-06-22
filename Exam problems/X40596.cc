#include <iostream>
#include <vector>
using namespace std;

void write(const vector<int>& sol, int n) {
    cout << '(';
    for (int i = 0; i < n; ++i) {
        if (i != 0) cout << ',';
        cout << sol[i];
    }
    cout << ')' << endl;
}

void seq(vector<int>& sol, vector<bool>& vis, int n, int d, int i) {
    if (i == n) write(sol, n);
    else {
        for (int j = 0; j < n; ++j) {
            if (not vis[j] and (i < 1 or abs(sol[i-1] - (j+1)) <= d)) {
                vis[j] = true;
                sol[i] = j+1;
                seq(sol, vis, n, d, i+1);
                vis[j] = false;
            }
        }
    }
}

int main() {
    int n, d;
    cin >> n >> d;
    vector<int> sol(n);
    vector<bool> vis(n, false);
    seq(sol, vis, n, d, 0);
}
