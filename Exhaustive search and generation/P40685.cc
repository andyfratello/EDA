#include <iostream>
#include <vector>
using namespace std;

void write(const vector<int>& v, const vector<bool>& vis, int n) {
    cout << '{';
    bool first = true;
    for (int i = 0; i < n; ++i) {
        if (vis[i]) {
            if (not first) cout << ',';
            else first = false;
            cout << v[i];
        }
    }
    cout << '}' << endl;
}

void sumes(vector<int>& v, vector<bool>& vis, int s, int n, int i, int sum) {
    if (n == i) {
        if (s == sum) write(v, vis, n);
    } else {
        vis[i] = false;
        sumes(v, vis, s, n, i+1, sum);
        vis[i] = true;
        sumes(v, vis, s, n, i+1, sum + v[i]);
    }
}

int main() {
    int s, n;
    cin >> s >> n;
    vector<int> v(n);
    for (int i = 0; i < n; ++i) cin >> v[i];
    vector<bool> vis(n);
    sumes(v, vis, s, n, 0, 0);
}
