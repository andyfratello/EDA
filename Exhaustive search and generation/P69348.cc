#include <iostream>
#include <vector>
using namespace std;

void write(const vector<int>& v, int n) {
    cout << '(';
    for (int i = 0; i < n; ++i) {
        cout << v[i];
        if (i != n-1) cout << ',';
    }
    cout << ')' << endl;
}

void unaena(vector<int>& v, vector<bool>& b, int n, int i) {
    if (n == i) write(v, n);
    else {
        for (int j = 0; j < n; ++j) {
            if (not b[j]) {
                b[j] = true;
                v[i] = j + 1;
                unaena(v, b, n, i+1);
                b[j] = false;
            }
        }
    }
}

int main() {
    int n;
    cin >> n;
    vector<int> v(n);
    vector<bool> b(n, false);
    unaena(v, b, n, 0);
}
