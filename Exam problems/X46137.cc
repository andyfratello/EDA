#include <iostream>
#include <vector>
using namespace std;

void compensades(string& s, int n, int i, int na, int nb) {
    if (i == n) cout << s << endl;
    else {
        if (abs((na + 1) - nb) <= 2) {
            s[i] = 'a';
            compensades(s, n, i+1, na+1, nb);
        }
        if (abs(na - (nb + 1)) <= 2) {
            s[i] = 'b';
            compensades(s, n, i+1, na, nb+1);
        }
    }
}

int main() {
    int n;
    cin >> n;
    string s(n, ' ');
    compensades(s, n, 0, 0, 0);
}
