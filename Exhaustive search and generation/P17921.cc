#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<char> > Board;
typedef vector<bool> VB;

int diag1(int n, int i, int j) {
    return n + i - j - 1;
}

int diag2(int i, int j) {
    return i + j;
}

void write(const Board& B, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) cout << B[i][j];
        cout << endl;
    }
    cout << endl;
}

void queen(Board& B, VB& col, VB& d1, VB& d2, int n, int i) {
    if (n == i) write(B, n);
    else {
        for (int j = 0; j < n; ++j) {
            if (not col[j] and not d1[diag1(n, i, j)] and not d2[diag2(i, j)]) {
                B[i][j] = 'Q';
                col[j] = true;
                d1[diag1(n, i, j)] = true;
                d2[diag2(i, j)] = true;
                queen(B, col, d1, d2, n, i+1);
                B[i][j] = '.';
                col[j] = false;
                d1[diag1(n, i, j)] = false;
                d2[diag2(i, j)] = false;
            }
        }
    }
}

int main() {
    int n;
    cin >> n;
    VB col(n, false);
    VB d1(2*n-1, false);
    VB d2(2*n-1, false);
    Board B(n, vector<char>(n, '.'));
    queen(B, col, d1, d2, n, 0);
}
