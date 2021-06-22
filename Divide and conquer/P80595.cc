#include <iostream>
#include <vector>
using namespace std;

int fusion(vector<int>& v, int left, int mid, int right) {
    int n = right - left + 1;
    int num = 0;
    vector<int> B(n);
    int i = left, j = mid + 1, k = 0;
    while (i <= mid and j <= right) {
        if (v[i] <= v[j]) B[k++] = v[i++];      // B[k] = v[i]; ++k; ++i;
        else {
            num += mid - i + 1;                 // Part de l'esquerra
            B[k++] = v[j++];                    // B[k] = v[i]; ++k; ++j;
        }
    }
    while (i <= mid) B[k++] = v[i++];
    while (j <= right) B[k++] = v[j++];
    for (k = 0; k < n; ++k) v[left + k] = B[k]; // Copia B a v
    return num;
}

int i_inversions(vector<int>& v, int left, int right) {
    if (left >= right) return 0;
    int mid = (left + right)/2;
    return i_inversions(v,left,mid) + i_inversions(v,mid+1,right) + fusion(v,left,mid,right);
}

int inversions(vector<int>& v) {
    return i_inversions(v,0,v.size() - 1);
}

int main() {
    int n;
    while (cin >> n) {
        vector<int> v(n);
        for (int i = 0; i < n; ++i) cin >> v[i];
        cout << inversions(v) << endl;
    }
}
