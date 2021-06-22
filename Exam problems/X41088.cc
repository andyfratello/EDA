#include <iostream>
#include <vector>
using namespace std;

void write(const vector<int>& v, int n) {
    cout << '(';
    for (int i = 0; i < n; ++i) {
        if (i != 0) cout << ',';
        cout << v[i];
    }
    cout << ')' << endl;
}

void pous(vector<int>& sol, vector<bool>& vis, int n, int i) {
    if (i == n) write(sol, n);
    else {
        for (int j = 0; j < n; ++j) {
            if (not vis[j] and (i < 2 or sol[i-2] + (j+1) <= 2*sol[i-1])) {
                vis[j] = true;
                sol[i] = j+1;
                pous(sol, vis, n, i+1);
                vis[j] = false;
            }
        }
    }
}

int main() {
    int n;
    cin >> n;
    vector<int> sol(n);
    vector<bool> vis(n, false);
    pous(sol, vis, n, 0);
}
