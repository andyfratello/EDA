// BFS
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef vector<vector<char> > Board;
typedef pair<int, int> Pos; //Coordenades
typedef vector<vector<int> > Dist;

const int X[4] = {1, 0, -1, 0};
const int Y[4] = {0, 1, 0, -1};

void read_board(Board& B, int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) cin >> B[i][j];
    }
}

int trobarTresor(Board& B, int n, int m, int f, int c) {
    queue<Pos> q;
    Dist d(n, vector<int>(m, -1));
    q.push(Pos(f, c));
    d[f][c] = 0;
    while (not q.empty()) {
        Pos p = q.front();
        q.pop();
        for (int i = 0; i < 4; ++i) {
            int x = X[i] + p.first;
            int y = Y[i] + p.second;
            if (x < n and x >= 0 and y < m and y >= 0 and B[x][y] != 'X' and d[x][y] == -1) {
                q.push(Pos(x, y));
                d[x][y] = d[p.first][p.second] + 1;
                if (B[x][y] == 't') return d[x][y];
            }
        }
    }
    return -1;
}

int main() {
    int n, m, f, c; 
    cin >> n >> m;
    Board B(n, vector<char>(m));
    read_board(B, n, m);
    cin >> f >> c;
    int d = trobarTresor(B, n, m, f - 1, c - 1);
    if (d == -1) cout << "no es pot arribar a cap tresor" << endl;
    else cout << "distancia minima: " << d << endl;
}
