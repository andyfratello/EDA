#include <iostream>
#include <queue>
using namespace std;

int main() {
    cout.setf(ios::fixed);
    cout.precision(4);
    priority_queue<int, vector<int>, greater<int>> q;
    string op;
    int n;
    int max;
    double sum = 0;
    while (cin >> op) {
        if (op == "number") {
            cin >> n;
            if (q.empty()) max = n;
            else if (max < n) max = n;
            sum += n;
            q.push(n);
        } else if (not q.empty() and op == "delete") {
            sum -= q.top();
            q.pop();
        }
        if (not q.empty()) cout << "minimum: " << q.top() << ", maximum: " << max << ", average: " << sum/q.size() << endl;
        else cout << "no elements" << endl;
    }
}
