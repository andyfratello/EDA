#include <iostream>
#include <vector>
using namespace std;

void write(const vector<int>& v, int n) {
    for (int i = 0; i < n; ++i) {
        if (i != 0) cout << ' ';
        cout << v[i];
    }
    cout << endl;
}

void zu(vector<int>& v, int n, int i) {
    if (i == n) write(v, n);
    else {
        v[i] = 0;
        zu(v, n, i+1);
        v[i] = 1;
        zu(v, n, i+1);
    }
}

int main() {
    int n;
    cin >> n;
    vector<int> v(n);
    zu(v, n, 0);
}
