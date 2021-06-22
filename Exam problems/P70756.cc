#include <iostream>
#include <vector>
using namespace std;

void write(const vector<string>& v, const vector<int>& sol, int n, int p) {
    for (int i = 0; i < p; ++i) {
        cout << "subconjunt " << i+1 << ": {";
        bool found = true;
        for (int j = 0; j < n; ++j) {
            if (sol[j] == i) {
                if (found) found = false;
                else cout << ',';
                cout << v[j];
            }
        }
        cout << '}' << endl;
    }
    cout << endl;
}

void particions(vector<string>& v, vector<int>& sol, int n, int p, int i) {
    if (n == i) write(v, sol, n, p);
    else {
        for (int j = 0; j < p; ++j) {
            sol[i] = j;
            particions(v, sol, n, p, i+1); 
        }
    }
}

int main() {
    int n;
    cin >> n;
    vector<string> v(n);
    for (int i = 0; i < n; ++i) cin >> v[i];
    int p;
    cin >> p;
    vector<int> sol(n);
    particions(v, sol, n, p, 0);
}
