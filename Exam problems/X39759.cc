#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef vector<vector<int> > Board;
typedef pair<int, int> Pos;

//vector<Pos> Dir = {{-2, 1}, {-1, 2}, {1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -1}, {-2, -1}};

const int X[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
const int Y[8] = {1, 2, 2, 1, -1, -2, -2, -1};


int bfs(const Pos& orig, const Pos& dest, int n, int m) {
    if (orig == dest) return 0;
    Board B(n, vector<int>(m, -1));
    queue<Pos> q;
    q.push(orig);
    B[orig.first][orig.second] = 0;
    while (not q.empty()) {
        Pos p = q.front();
        q.pop();
        for (int i = 0; i < 8; ++i) {
            int x = p.first + X[i];
            int y = p.second + Y[i];
            if (Pos(x, y) == dest) return B[p.first][p.second] + 1;
            else if (x >= 0 and y >= 0 and x < n and y < m and B[x][y] == -1) {
                q.push(Pos(x, y));
                B[x][y] = B[p.first][p.second] + 1;
            }
        }
    }
    return -1;
}

int main() {
    int n, m, w, l, k;
    while (cin >> n >> m >> w >> l >> k) {
        vector<Pos> v(k+1);
        v[0] = Pos(0,0);
        for (int i = 1; i <= k; ++i) cin >> v[i].first >> v[i].second;
        int punts = 0;
        int max_punts = 0;
        bool end = false;
        for (int i = 0; not end and i < k; ++i) {
            int dist = bfs(v[i], v[i+1], n, m);
            if (dist == -1) end = true;
            else {
                punts += w;
                punts -= l*dist;
                if (punts > max_punts) max_punts = punts;
            }
        }
        cout << max_punts << endl;
    }
}
