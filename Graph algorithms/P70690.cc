//DFS
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef vector<vector<char>> Board;

void read_board(Board& b, int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) cin >> b[i][j];
    }
}

void trobarTresor(Board& B, vector<vector<bool>>& visitat, int f, int c, bool& trobat) {
    int n = B.size();
    int m = B[0].size();
    if (not visitat[f][c] and not trobat) {
        visitat[f][c] = true;
        if (B[f][c] == 't') trobat = true;
        else if (B[f][c] != 'X') {
            if (f != n - 1) trobarTresor(B, visitat, f + 1, c, trobat);
            if (f != 0) trobarTresor(B, visitat, f - 1, c, trobat);
            if (c != m - 1) trobarTresor(B, visitat, f, c + 1, trobat);
            if (c != 0) trobarTresor(B, visitat, f, c - 1, trobat);
        }
    }
}

int main() {
    int n, m, f, c;
    cin >> n >> m;
    Board b(n, vector<char>(m));
    read_board(b, n, m);
    cin >> f >> c;
    vector<vector<bool> > visitat(n, vector<bool>(m, false));
    bool trobat = false;
    trobarTresor(b, visitat, f - 1, c - 1, trobat);
    if (trobat) cout << "yes" << endl;
    else cout << "no" << endl;
}
