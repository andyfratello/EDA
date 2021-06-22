#include <iostream>
#include <vector>
#include <map>
using namespace std;

typedef map<string, int>::iterator Iter;

int main() {
    int n;
    while (cin >> n) {
        map<string, int> M;
        int total = 0;
        for (int i = 0; i < n; ++i) { // col·lecció inicial
            string s;
            cin >> s;
            ++total;
            ++M[s];
        }
        cin >> n;
        for (int i = 0; i < n; ++i) { // nous jocs disponibles
            string s;
            cin >> s;
            Iter it = M.find(s);
            int num = 0;
            if (it != M.end()) num = it->second;

            if (num + 1 <= total - num) {
                ++M[s];
                ++total;
            }
        }
        Iter it;
        for (it = M.begin(); it != M.end(); ++it) {
            cout << it->first << ' ' << it->second << endl;
        }
        cout << string(20, '-') << endl;
    }
}
