#include <iostream>
#include <map>
using namespace std;

int main() {
    int x, y, n;
    while (cin >> x >> y >> n) {
        map<int, int> M;
        map<int, int>::iterator it;
        bool repeated = false;
        int pos = 0;
        M.insert(make_pair(n, 0));
        while (n <= 100000000 and not repeated) {
            ++pos;
            if (n%2 == 0) n = n/2 + x;
            else n = 3*n + y;
            it = M.find(n);
            if (it == M.end()) M.insert(make_pair(n, pos));
            else repeated = true;
        }
        if (repeated) cout << M.size() - it->second << endl;
        else cout << n << endl;
    }
}
