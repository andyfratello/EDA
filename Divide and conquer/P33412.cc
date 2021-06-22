#include <iostream>
#include <vector>
using namespace std;

bool i_resistant_search(double x, const vector<double>& v, int left, int right) {
    if (left > right) return false;
    int mid = (left+right)/2;
    if (v[mid] == x) return true;
    else if (v[mid] > x) {
        if (v[mid + 1] == x and mid < right) return true;
        return i_resistant_search(x,v,left,mid - 1);
    }
    else {
        if (v[mid - 1] == x and mid > left) return true;
        return i_resistant_search(x,v,mid + 1,right);
    }
}

bool resistant_search(double x, const vector<double>& v) {
    return i_resistant_search(x,v,0,v.size()-1);
}

int main() {
    int n;
    while (cin >> n) {
        vector<double> V(n);
        for (int i = 0; i < n; ++i) cin >> V[i];
        int t;
        cin >> t;
        while (t--) {
            double x;
            cin >> x;
            cout << resistant_search(x, V) << endl;
        }
    }
}
