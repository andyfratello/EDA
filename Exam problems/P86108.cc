#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<char> > Mapa;

void next (int i, int j, int& ni, int& nj, int m) {
    if (j == m-1) {
        ni = i+1;
        nj = 0;
    } else {
        ni = i;
        nj = j+1;
    }
}

int back(Mapa& sol, int n, int m, int i, int j, int num) {
    if (i == n) return num;
    int ni, nj;
    next(i, j, ni, nj, m);
    sol[i][j] = 'L';
    int num_lol = 0;
    
    // comprovem que s'ha creat un LOL horitzontal
    if (j >= 2 and sol[i][j-1] == 'O' and sol[i][j-2] == 'L') ++num_lol;
    // comprovem si s'ha format un LOL diagonal esq-dre
    if (i >= 2 and j >= 2 and sol[i-1][j-1] == 'O' and sol[i-2][j-2] == 'L') ++num_lol;
    // comprovem si s0ha format un LOL en vertical
    if (i >= 2 and sol[i-1][j] == 'O' and sol[i-2][j] == 'L') ++num_lol;
    // comprovem si s'ha format un LOL diagonal dre-esq
    if (i >= 2 and j < m-1 and sol[i-1][j+1] == 'O' and sol[i-2][j+2] == 'L') ++num_lol;
    
    int num_l = back(sol, n, m, ni, nj, num + num_lol);
    // num_l és el màxim num. de LOLs posant una L a la posició [i, j]

    sol[i][j] = 'O';
    int num_o = back(sol, n, m, ni, nj, num);
    // num_o és el màxim num. de LOLs posant una O a la posició [i, j]

    return max(num_l, num_o);
}

int main() {
    int n, m;
    while (cin >> n >> m) {
        Mapa sol(n, vector<char>(m));
        cout << back(sol, n, m, 0, 0, 0) << endl;
    }
}
