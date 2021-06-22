#include <iostream>
#include <vector>
using namespace std;

int i_first_occurrence(double x, const vector<double>& v, int left, int right) {
    if (left > right) return -1;
    int mid = (left+right)/2;
    if (left == right) {
        if (x == v[right]) return right;
        return -1;
    }
    if (v[mid] >= x) return i_first_occurrence(x,v,left,mid);
    if (v[mid] < x) return i_first_occurrence(x,v,mid + 1,right);
}

int first_occurrence(double x, const vector<double>& v) {
    return i_first_occurrence(x,v,0,v.size()-1);
}

int main() {
    int n;
    cin >> n;
    vector<double> V(n);
    for (int i = 0; i < n; ++i) cin >> V[i];
    double x;
    cin >> x;
    cout << first_occurrence(x, V) << endl;
}
