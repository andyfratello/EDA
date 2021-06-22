#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
using namespace std;

const int infinit = INT_MAX;

typedef pair<int, int> ArcP;
typedef vector<vector<ArcP> > Graf;

int carreteres(Graf& G, int n, int a, int b) {
    vector<bool> vis(n, false);
    vector<int> dis(n, infinit);
    dis[a] = 0;
    priority_queue<ArcP, vector<ArcP>, greater<ArcP>> Q;
    Q.push(ArcP(0, a));
    while (not Q.empty()) {
        int u = Q.top().second;
        int du = Q.top().first;
        Q.pop();
        if (not vis[u]) {
            vis[u] = true;
            if (u == b) return dis[b];
            if (du == dis[u]) {
                for (ArcP p : G[u]) {
                    int dv = p.first;
                    int v = p.second;
                    if (dis[v] > max(dis[u], dv)) {
                        dis[v] = max(dis[u], dv);
                        Q.push(ArcP(dis[v], v));
                    }
                }
            }
        }
    }
    return infinit;
}

int main() {
    int n, m;
    while (cin >> n >> m) {
        Graf G(n);
        for (int i = 0; i < m; ++i) {
            int a, b, d;
            cin >> a >> b >> d;
            G[a].push_back(ArcP(d, b));
        }
        cout << carreteres(G, n, 0, 1) << endl;
    }
}
