#include <iostream>
#include <vector>
using namespace std;

void write (const vector<int>& v, int n) {
    for (int i = 0; i < n; ++i) {
        if (i != 0) cout << ' ';
        cout << v[i];
    }
    cout << endl;
}

void zu(vector<int>& v, int n, int u, int i, int numUns) {
    if (numUns <= u and n - u >= i - numUns) {
        if (i == n) write(v, n);
        else {
            v[i] = 0;
            zu(v, n, u, i+1, numUns);
            v[i] = 1;
            zu(v, n, u, i+1, numUns+1);
        }
    }
}

int main() {
    int n, u;
    cin >> n >> u;
    vector<int> v(n);
    zu(v, n, u, 0, 0);
}
