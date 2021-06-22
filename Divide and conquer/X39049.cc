#include <iostream>
#include <vector>
using namespace std;

vector<int> compos(const vector<int>& v1, const vector<int>& v2) {
    int n = v1.size();
    vector<int> sol(n);
    for (int i = 0; i < n; ++i) {
        sol[i] = v1[v2[i]];
    }
    return sol;
}

void potencias_perm(const vector<int>& v, int k, vector<int>& sol) {
    int n = v.size();
    if (k == 0) {
        for (int i = 0; i < n; ++i) sol[i] = i;
    } else {
        vector<int> aux(n);
        potencias_perm(v, k/2, aux);
        sol = compos(aux, aux);
        if (k%2 != 0) sol = compos(sol, v);
    }
}

int main() {
    int n;
    while (cin >> n) {
        vector<int> v(n);
        vector<int> sol(n);
        for (int i = 0; i < n; ++i) cin >> v[i];
        int k;
        cin >> k;
        potencias_perm(v, k, sol);
        for (int i = 0; i < n; ++i) {
            if (i != 0) cout << ' ';
            cout << sol[i];
        }
        cout << endl;
    }
}
