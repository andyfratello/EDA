#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef pair<int, int> ArcP;
typedef vector<vector<ArcP> > Graf;

int retallades(const Graf& G, int n) {
    vector<bool> vis(n, false);
    vis[0] = true;
    priority_queue<ArcP, vector<ArcP>, greater<ArcP> > Q;
    for (ArcP p : G[0]) Q.push(p);
    int c = 1; // vèrtexs visitats
    int s = 0; // indica el cost del MST
    while (c != n) {
        int cost = Q.top().first;
        int u = Q.top().second;
        Q.pop();
        if (not vis[u]) {
            for (ArcP p : G[u]) Q.push(p);
            vis[u] = true;
            ++c;
            s += cost;
        }
    }
    return s;
}

int main() {
    int n, m;
    while (cin >> n >> m) {
        int x, y, c;
        Graf G(n);
        int total = 0;
        for (int i = 0; i < m; ++i) {
            cin >> x >> y >> c;
            total += c;
            G[x].push_back(ArcP(c, y));
            G[y].push_back(ArcP(c, x));
        }
        int estalvi = retallades(G, n);
        cout << total - estalvi << endl;
    }
}
