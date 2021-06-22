#include <iostream>
#include <vector>
using namespace std;

void pujades_baixades(string& s, int n, int i, int height) {
    if (i == n) cout << s << endl;
    else {
        if (height != 0) {
            s[i] = 'd';
            pujades_baixades(s, n, i+1, height-1);
        }
        s[i] = 'h';
        pujades_baixades(s, n, i+1, height);
        s[i] = 'u';
        pujades_baixades(s, n, i+1, height+1);
    }
}

int main() {
    int n; 
    cin >> n;
    string s(n, ' ');
    pujades_baixades(s, n, 0, 0);
}
