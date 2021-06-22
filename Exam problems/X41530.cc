#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<int>> Grafo;

// DFS
bool hay_ciclo (const Grafo& g, int u, vector<bool>& vis, int vant) { // u --> vèrtex actual // vant--> vèrtex anterior
    bool ciclo;
    if (vis[u]) ciclo = true;
    else {
        vis[u] = true;
        ciclo = false;
        for (int i = 0; i < g[u].size() and not ciclo; ++i) { // for (int adj : g[u])
            int adj = g[u][i];
            if (adj != vant) ciclo = hay_ciclo(g, adj, vis, u);
        }
    }
    return ciclo;
}

int bosc(const Grafo& g) {
    int n_arb = 0;
    vector<bool> vis(g.size(), false);
    bool ciclo = false;
    int i = 0;
    while (i < g.size() and not ciclo) {
        if (not vis[i]) {
            if (hay_ciclo(g, i, vis, -1)) ciclo = true;
            else ++n_arb;
        }
        ++i;
    }
    if (ciclo) n_arb = -1;
    return n_arb;
}

int main() {
    int n, m;
    while (cin >> n >> m) {
        Grafo G(n);
        int x, y;
        for (int i = 0; i < m; ++i) {
            cin >> x >> y;
            G[x].push_back(y);
            G[y].push_back(x);
        }
        int n_arb = bosc(G);
        if (n_arb == -1) cout << "no" << endl;
        else cout << n_arb << endl;
    }
}
