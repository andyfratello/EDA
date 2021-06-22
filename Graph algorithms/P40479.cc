#include <iostream>
#include <vector>
#include <stack>
using namespace std;

typedef vector<vector<char> > Tauler;
typedef pair<int, int> Pos;

int X[4] = {1, 0, -1, 0};
int Y[4] = {0, 1, 0, -1};

void read_tauler(Tauler& T, int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) cin >> T[i][j];
    }
}

void pintar_tauler_dfs(Tauler& T, char c, int i, int j) {
    stack<Pos> S;
    S.push(Pos(i, j));
    while (not S.empty()) {
        Pos p = S.top();
        S.pop();
        for (int k = 0; k < 4; ++k) {
            int x = p.first + X[k];
            int y = p.second + Y[k];
            if (T[x][y] == '.') {
                T[x][y] = c;
                S.push(Pos(x, y));
            }
        }
    }
}

void pintar_tauler(Tauler& T, int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (T[i][j] != '#' and T[i][j] != '.') {
                pintar_tauler_dfs(T, T[i][j], i, j);
            }
        }
    }
}

void write_tauler(const Tauler& T, int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) cout << T[i][j];
        cout << endl;
    }
    cout << endl;
}

int main() {
    int n, m;
    while (cin >> n >> m) {
        Tauler T(n, vector<char>(m));
        read_tauler(T, n, m);
        pintar_tauler(T, n, m);
        write_tauler(T, n, m);
    }
}
