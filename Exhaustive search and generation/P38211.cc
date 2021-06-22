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
}

bool queen(Board& B, VB& col, VB& d1, VB& d2, int n, int i) {
    if (n == i) return true;
    else {
        for (int j = 0; j < n; ++j) {
            if (not col[j] and not d1[diag1(n, i, j)] and not d2[diag2(i, j)]) {
                B[i][j] = 'Q';
                col[j] = true;
                d1[diag1(n, i, j)] = true;
                d2[diag2(i, j)] = true;
                bool b = queen(B, col, d1, d2, n, i+1);
                if (b) return true;
                B[i][j] = '.';
                col[j] = false;
                d1[diag1(n, i, j)] = false;
                d2[diag2(i, j)] = false;
            }
        }
        return false;
    }
}

int main() {
    int n;
    cin >> n;
    VB col(n);
    VB d1(2*n-1);
    VB d2(2*n-1);
    Board B(n, vector<char>(n, '.'));
    if (queen(B, col, d1, d2, n, 0)) write(B, n);
    else cout << "NO SOLUTION" << endl;
}
