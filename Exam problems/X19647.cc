#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
using namespace std;

typedef pair<int, int> Arcp; //dist, vÃ¨rtex adjacent
typedef vector<vector<Arcp>> Graf;

const int infinit = INT_MAX;

int coste_minimo(const Graf& g, const vector<int>& v_c, int a, int b) {
    int n = g.size();
    vector<int> dist(n, infinit);
    dist[a] = 0; 
    vector<bool> vis(n, false);
    priority_queue<Arcp, vector<Arcp>, greater<Arcp>> PQ;
    PQ.push(Arcp(0, a));
    while (not PQ.empty()) {
        Arcp a = PQ.top();
        PQ.pop();
        int du = a.first;
        int u = a.second;
        if (u == b) return dist[u];
        if (not vis[u]) {
            vis[u] = true;
            for (Arcp p : g[u]) {
                int v = p.second;
                int dv = p.first;
                int coste_v = dist[u] + dv;
                if (v != b) coste_v += v_c[v];
                if (dist[v] > coste_v) {
                    dist[v] = coste_v;
                    PQ.push(Arcp(coste_v, v));
                }
            }
        }
    }
    return infinit;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> v_c(n);
    for (int i = 0; i < n; ++i) cin >> v_c[i];
    Graf g(n);
    for (int i = 0; i < m; ++i) {
        int u, v, d;
        cin >> u >> v >> d;
        g[u].push_back(Arcp(d, v));
        g[v].push_back(Arcp(d, u));
    }
    int a, b;
    while (cin >> a >> b) {
        int cost = coste_minimo(g, v_c, a, b);
        cout << "c(" << a << ',' << b << ") = ";
        if (cost != infinit) cout << cost << endl;
        else cout << "+oo" << endl;
    }
}
