#include <iostream>
#include <vector>
#include <list>
#include <queue>
using namespace std;

typedef vector<vector<int> > Graf;

list<int> topologica(Graf& G, int n) {
    vector<int> ge(n, 0);
    for (int i = 0; i < n; ++i) {
        for (int v : G[i]) ++ge[v];
    }
    priority_queue<int, vector<int>, greater<int>> q;
    for (int i = 0; i < n; ++i) {
        if (ge[i] == 0) q.push(i);
    }
    list<int> L;
    while (not q.empty()) {
        int u = q.top();
        q.pop();
        L.push_back(u);
        for (int v : G[u]) {
            --ge[v];
            if (ge[v] == 0) q.push(v);
        }
    }
    return L;
}

int main() {
    int n, m;
    while (cin >> n >> m) {
        Graf G(n);
        int x, y;
        for (int i = 0; i < m; ++i) {
            cin >> x >> y;
            G[x].push_back(y);
        }
        list<int> L = topologica(G, n);
        list<int>::iterator it;
        bool first = true;
        for (it = L.begin(); it != L.end(); ++it) {
            if (first) first = false;
            else cout << ' ';
            cout << *it;
        }
        cout << endl;
    }
}
