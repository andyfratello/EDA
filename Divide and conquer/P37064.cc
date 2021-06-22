#include <iostream>
#include <set>
using namespace std;

int main() {
    set<string> S;
    set<string>::iterator median = S.end();
    set<string>::iterator it;
    string s;
    cin >> s;
    while (s != "END") {
        S.insert(s);
        it = S.find(s);
        if (median == S.end()) median = it;
        else if (S.size()%2 == 0 and s < *median) --median;
        else if (S.size()%2 != 0 and s > *median) ++median;
        cout << *median << endl;
        cin >> s;
    }
}
