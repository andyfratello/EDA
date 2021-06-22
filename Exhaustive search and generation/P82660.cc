#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool comp(int a, int b) {
    return a > b;
}

void write(const vector<int>& v, const vector<bool>& sol, int n) {
    cout << '{';
    bool first = true;
    for (int i = 0; i < n; ++i) {
        if (sol[i]) {
            if (first) first = false;
            else cout << ',';
            cout << v[i];
        }
    }
    cout << '}' << endl;
}

bool sumes(vector<int>& v, vector<bool>& sol, int s, int n, int i, int sum) {
    if (n == i) {
        if (s == sum) {
            write(v, sol, n);
            return true;
        }
        else return false;
    } else {
        sol[i] = true;
        bool b = sumes(v, sol, s, n, i+1, sum + v[i]);
        if (not b) {
            sol[i] = false;
            return sumes(v, sol, s, n, i+1, sum);
        } else return true;
    }
}

int main() {
    int s, n;
    cin >> s >> n;
    vector<int> v(n);
    for (int i = 0; i < n; ++i) cin >> v[i];
    vector<bool> sol(n);
    sort(v.begin(), v.end(), comp);
    if (not sumes(v, sol, s, n, 0, 0)) cout << "no solution" << endl;
}
 
