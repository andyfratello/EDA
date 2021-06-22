#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef vector<vector<char>> Board;
typedef pair<int, int> Pos;

vector<Pos> dirFantasma = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};

const int X[4] = {1, 0, -1, 0};
const int Y[4] = {0, 1, 0, -1};

bool bfs(Board& B, int xp, int yp) {
    queue<Pos> q;
    q.push(Pos(xp, yp));
    B[xp][yp] = 'X';
    while (not q.empty()) {
        Pos p = q.front();
        q.pop();
        for (int i = 0; i < 4; ++i) {
            int x = p.first + X[i];
            int y = p.second + Y[i];
            if (B[x][y] == 'B') return true;
            else if (B[x][y] == '.') {
                q.push(Pos(x, y));
                B[x][y] = 'X';
            }
        }
    }
    return false;
}

int main() {
    int n, m;
    while (cin >> n >> m) {
        int xp, yp;
        queue<Pos> q;
        Board B(n, vector<char>(m));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cin >> B[i][j];
                if (B[i][j] == 'P') {
                    xp = i;
                    yp = j;
                } else if (B[i][j] == 'F') q.push(Pos(i, j));
            }
        }
        // rodejar el fantasma de X
        bool alive = true;
        while (alive and not q.empty()) {
            Pos pFantasma = q.front();
            q.pop();
            for (int i = 0; i < 8; ++i) {
                int x = pFantasma.first + dirFantasma[i].first;
                int y = pFantasma.second + dirFantasma[i].second;
                if (B[x][y] == 'P') {
                    alive = false;
                    break;
                } 
                B[x][y] = 'X';
            }
        }
        if (alive and bfs(B, xp, yp)) cout << "si" << endl; 
        else cout << "no" << endl;
    }
}
