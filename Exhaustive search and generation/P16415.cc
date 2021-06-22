#include <iostream>
#include <vector>
using namespace std;

typedef vector<bool> VB;

int diag1(int n, int i, int j) {
    return n + i - j - 1;
}

int diag2(int i, int j) {
    return i + j;
}

int queen(VB& col, VB& d1, VB& d2, int n, int i) {
    if (n == i) return 1;
    else {
        int count = 0;
        for (int j = 0; j < n; ++j) {
            if (not col[j] and not d1[diag1(n, i, j)] and not d2[diag2(i, j)]) {
                col[j] = true;
                d1[diag1(n, i, j)] = true;
                d2[diag2(i, j)] = true;
                count += queen(col, d1, d2, n, i+1);
                col[j] = false;
                d1[diag1(n, i, j)] = false;
                d2[diag2(i, j)] = false;
            }
        }
        return count;
    }
}

int main() {
    int n;
    cin >> n;
    VB col(n, false);
    VB d1(2*n-1, false);
    VB d2(2*n-1, false);
    cout << queen(col, d1, d2, n, 0) << endl;
}
