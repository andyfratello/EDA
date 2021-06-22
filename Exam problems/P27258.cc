#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef vector<vector<char> > Mapa;
typedef pair<int, int> Pos;

const int X[4] = {-1, 0, 1, 0};
const int Y[4] = {0, -1, 0, 1};

bool pos_ok(int f, int c, const Mapa& mapa) {
    return f >= 0 and c >= 0 and f < mapa.size() and c < mapa[0].size();
}

bool DFS(Mapa& mapa, const Pos& ini, const Pos& fin) {
    if (mapa[ini.first][ini.second] == 'X') return false;
    mapa[ini.first][ini.second] = 'X';
    if (ini == fin) return true;
    for (int i = 0; i < 4; ++i) {
        int x = ini.first + X[i];
        int y = ini.second + Y[i];
        if (pos_ok(x, y, mapa) and mapa[x][y] != 'X') {
            Pos next(x, y);
            if (DFS(mapa, next, fin)) return true;
        }
    }
    return false;
}

int main() {
    int n, m;
    while (cin >> n >> m) {
        Pos ini, fin;
        queue<Pos> monstres;
        Mapa mapa(n, vector<char>(m));

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cin >> mapa[i][j];
                if (mapa[i][j] == 'I') ini = Pos(i, j);
                else if (mapa[i][j] == 'F') fin = Pos(i, j);
                else if (mapa[i][j] == 'M') monstres.push(Pos(i, j));
            }
        }
        while (not monstres.empty()) {
            Pos p = monstres.front();
            monstres.pop();
            for (int i = 0; i < 4; ++i) {
                int x = p.first + X[i];
                int y = p.second + Y[i];
                if (pos_ok(x, y, mapa) and mapa[x][y] != 'M') mapa[x][y] = 'X';
            }
        }
        bool b = DFS(mapa, ini, fin);
        if (b) cout << "SI" << endl;
        else cout << "NO" << endl;
    }
}
