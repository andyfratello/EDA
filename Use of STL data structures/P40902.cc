#include <iostream>
#include <map>
using namespace std;

int main() {
    string name, op;
    int n;
    map<string, int> M;
    map<string, int>::iterator it;
    while (cin >> name >> op) {
        it = M.find(name);
        if (op == "enters") {
            if (it != M.end()) cout << name << " is already in the casino" << endl;
            else M.insert(make_pair(name, 0));
        } else if (op == "leaves") {
            if (it == M.end()) cout << name << " is not in the casino" << endl;
            else {
                cout << name << " has won " << it->second << endl;
                M.erase(it);
            }
        } else { // op == "wins"
            cin >> n;
            if (it == M.end()) cout << name << " is not in the casino" << endl;
            else it->second += n;
        }
    }
    cout << string(10, '-') << endl;
    for (it = M.begin(); it != M.end(); ++it) {
        cout << it->first << " is winning " << it->second << endl;
    }
}
 
