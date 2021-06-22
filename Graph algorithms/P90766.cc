// DFS
#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<char> > Board;
typedef vector<vector<bool> > Visited;

void read_board(Board& B, int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) cin >> B[i][j];
    }
}

void trobarTresor(const Board& B, Visited& vis, int n, int m, int f, int c, int& count) {
    if (not vis[f][c]) {
        vis[f][c] = true;
        if (B[f][c] == 't') ++count;
        if (B[f][c] != 'X') {
            if (f != 0) trobarTresor(B, vis, n, m, f - 1, c, count);
            if (f != n - 1) trobarTresor(B, vis, n, m, f + 1, c, count);
            if (c != 0) trobarTresor(B, vis, n, m, f, c - 1, count);
            if (c != m - 1) trobarTresor(B, vis, n, m, f, c + 1, count);
        } 
    }
}

int main() {
    int n, m, f, c;
    cin >> n >> m;
    Board B(n, vector<char>(m));
    read_board(B, n, m);
    cin >> f >> c;
    Visited vis(n, vector<bool>(m, false));
    int count = 0;
    trobarTresor(B, vis, n, m, f - 1, c - 1, count);
    cout << count << endl;
}
