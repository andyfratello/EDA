#include <iostream>
#include <vector>
#include <sstream>
#include <queue>
using namespace std;

typedef vector<queue<string>> VQ;

int main() {
    int n;
    cin >> n;
    VQ v(n);
    string s;
    getline(cin, s);
    for (int i = 0; i < n; ++i) {
        string s;
        getline(cin, s);
        istringstream ss(s);
        string x;
        while (ss >> x) v[i].push(x);
    }

    string op;
    vector<string> sortides;
    while (cin >> op) {
        if (op == "SURT") {
            int a;
            cin >> a;
            if (a > 0 and a - 1 < n and not v[a-1].empty()) {
                sortides.push_back(v[a-1].front());
                v[a-1].pop();
            }
        } else { // ENTRA
            string name;
            int a;
            cin >> name >> a;
            if (a > 0 and a - 1 < n) {
                v[a-1].push(name);
            }
        }
    }

    cout << "SORTIDES" << endl;
    cout << "--------" << endl;
    for (int i = 0; i < sortides.size(); ++i) {
        cout << sortides[i] << endl;
    }
    cout << endl;
    cout << "CONTINGUTS FINALS" << endl;
    cout << "-----------------" << endl;
    for (int i = 0; i < n; ++i) {
        cout << "cua " << i+1 << ':';
        while (not v[i].empty()) {
            cout << " " << v[i].front();
            v[i].pop();
        }
        cout << endl;
    }
}
