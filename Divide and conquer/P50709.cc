#include <iostream>
#include <queue>
using namespace std;

int main() {
    char c;
    int n;
    priority_queue<int> q;
    while (cin >> c) {
        if (c == 'S') {
            cin >> n;
            q.push(n);
        } else if (c == 'A') {
            if (q.empty()) cout << "error!" << endl;
            else cout << q.top() << endl;
        } else if (c == 'R') {
            if (q.empty()) cout << "error!" << endl;
            else q.pop();
        } else if (c == 'I') {
            cin >> n;
            if (q.empty()) cout << "error!" << endl;
            else {
                int aux = q.top() + n;
                q.pop();
                q.push(aux);
            }
        } else {
            cin >> n;
            if (q.empty()) cout << "error!" << endl;
            else {
                int aux = q.top() - n;
                q.pop();
                q.push(aux);
            }
        }
    }
}
