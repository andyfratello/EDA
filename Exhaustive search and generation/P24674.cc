#include <iostream>
#include <vector>
using namespace std;

void write(const vector<string>& v, const vector<int>& sol, int n) {
    cout << '(';
    for (int i = 0; i < n; ++i) {
        if (i != 0) cout << ',';
        cout << v[sol[i]];
    } 
    cout << ')' << endl;
}

void permut(const vector<string>& v, vector<int>& sol, vector<bool>& vis, int n, int i) {
    if (i == n) write(v, sol, n);
    else {
        for (int j = 0; j < n; ++j) {
            if (not vis[j]) {
                vis[j] = true;
                sol[i] = j;
                permut(v, sol, vis, n, i+1);
                vis[j] = false;
            } 
        }
    }
}

int main() {
    int n;
    cin >> n;
    vector<string> v(n);
    for (int i = 0; i < n; ++i) cin >> v[i];
    vector<int> sol(n);
    vector<bool> vis(n);
    permut(v, sol, vis, n, 0);
}
