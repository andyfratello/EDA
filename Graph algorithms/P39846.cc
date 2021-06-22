#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef vector<vector<char> > Board;
typedef vector<vector<int> > BI;
typedef pair<int, int> Pos;

const int X[4] = {1, 0, -1, 0};
const int Y[4] = {0, -1, 0, 1};

int bfs(Board& B, int n, int m, int f, int c) {
    queue<Pos> q;
    q.push(Pos(f, c));
    BI Dist(n, vector<int>(m, -1));
    Dist[f][c] = 0;
    int d = 0;
    while (not q.empty()) {
        Pos p = q.front();
        q.pop();
        for (int i = 0; i < 4; ++i) {
            int x = p.first + X[i];
            int y = p.second + Y[i];
            if (x >= 0 and y >= 0 and x < n and y < m and Dist[x][y] == -1 and B[x][y] != 'X') {
                if (B[x][y] == 't') {
                    if (d < Dist[p.first][p.second] + 1) d = Dist[p.first][p.second] + 1;
                }
                q.push(Pos(x, y));
                Dist[x][y] = Dist[p.first][p.second] + 1;
                B[x][y] = 'X';
            }
        }
    }
    return d;
}

int main() {
    int n, m;
    cin >> n >> m;
    Board B(n, vector<char>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> B[i][j];
        }
    }
    int f, c;
    cin >> f >> c;
    int d = bfs(B, n, m, f-1, c-1);
    if (d == 0) cout << "no es pot arribar a cap tresor" << endl;
    else cout << "distancia maxima: " << d << endl;
}
