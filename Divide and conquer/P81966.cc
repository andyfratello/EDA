#include <iostream>
#include <vector>
using namespace std;

int position(double x, const vector<double>& v, int left, int right) {
    if (left > right) return -1;
    int mid = (left+right)/2;
    if (x == v[mid]) return mid;
    else if (x < v[mid]) return position(x,v,left,mid-1);
    else if (x > v[mid]) return position(x,v,mid+1,right);
}

int main() {
    int x, n;
    cin >> n >> x;
    vector<double> v(n);
    for (int i = 0; i < n; ++i) cin >> v[i];
    cout << position(x,v,0,v.size()-1) << endl;
}
