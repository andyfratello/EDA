#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef vector<vector<string>> Board;
typedef vector<vector<int>> BoardInt;
typedef pair<int, int> Pos;

const int X[4] = {-1, 0, 1, 0};
const int Y[4] = {0, -1, 0, 1};

int bfs(const Board& B, int n, int m, Pos ini, Pos dest) {
    if (ini == dest) return 0;
    queue<Pos> q;
    q.push(ini);
    BoardInt BI(n, vector<int>(m, -1));
    BI[ini.first][ini.second] = 0;
    while (not q.empty()) {
        Pos p = q.front();
        q.pop();
        for (int i = 0; i < 4; ++i) {
            int x = X[i] + p.first;
            int y = Y[i] + p.second;
            if (x >= 0 and y >= 0 and x < n and y < m and BI[x][y] == -1 and B[x][y] != "*") {
                if (Pos(x, y) == dest) return BI[p.first][p.second] + 1;
                else {
                    BI[x][y] = BI[p.first][p.second] + 1;
                    q.push(Pos(x, y));
                }
            }
        }
    }
    return -1;
}

Pos searchWord(const Board& B, int n, int m, string& s) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (B[i][j] == s) return Pos(i, j);
        }
    }
    return Pos(-1, -1);
}

int main() {
    int n, m;
    while (cin >> n >> m) {
        Board B(n, vector<string>(m));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cin >> B[i][j];
            }
        }
        int p;
        cin >> p;
        vector<string> v(p);
        for (int i = 0; i < p; ++i) cin >> v[i];

        vector<Pos> vp(p+1);
        vp[0] = Pos(0,0);
        for (int i = 1; i <= p; ++i) {
            Pos pW = searchWord(B, n, m, v[i-1]);
            vp[i] = pW;
        }

        bool impossible = false;
        int count = 0;
        for (int i = 0; not impossible and i < p; ++i) {
            int num = bfs(B, n, m, vp[i], vp[i+1]);
            if (num == -1) impossible = true;
            else count += num;
        }
        if (not impossible) cout << count + p << endl;
        else cout << "impossible" << endl;
    }
}
