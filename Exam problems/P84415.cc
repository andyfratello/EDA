#include <iostream>
#include <map>
using namespace std;

int main() {
    map<string, int> M;
    map<string, int>::iterator it;
    string s, word;
    while (cin >> s) {
        if (s == "store") {
            cin >> word;
            it = M.find(word);
            if (it != M.end()) ++it->second;
            else M.insert(make_pair(word,1));
        } else if (s == "delete") {
            cin >> word;
            it = M.find(word);
            if (it != M.end()) {
                --it->second;
                if (it->second == 0) M.erase(word);
            }
        } else if (s == "minimum?") {
            if (M.empty()) cout << "indefinite minimum" << endl;
            else {
                it = M.begin();
                cout << "minimum: " << it->first << ", " << it->second << " time(s)" << endl;
            }
        } else { // maximum?
            if (M.empty()) cout << "indefinite maximum" << endl;
            else {
                it = M.end();
                --it;
                cout << "maximum: " << it->first << ", " << it->second << " time(s)" << endl;
            }
        }
    }
}
