#include <iostream>
#include <vector>
using namespace std;

int buscaPosCim(const vector<int>& v, int esq, int dre) {
    if (esq == dre) return esq;
    else if (esq+1 == dre) {
        if (v[esq] > v[dre]) return esq;
        return dre;
    }
    int mid = (esq + dre)/2;
    if (v[mid] < v[mid - 1]) return buscaPosCim(v, esq, mid - 1);
    else if (v[mid] < v[mid + 1]) return buscaPosCim(v, mid + 1, dre);
    return mid;
}

bool searchCre(int x, const vector<int>& v, int esq, int dre) {
    if (esq > dre) return false;
    int mid = (esq + dre)/2;
    if (v[mid] > x) return searchCre(x, v, esq, mid - 1);
    else if (v[mid] < x) return searchCre(x, v, mid + 1, dre);
    return true;
}

bool searchDec(int x, const vector<int>& v, int esq, int dre) {
    if (esq > dre) return false;
    int mid = (esq + dre)/2;
    if (v[mid] < x) return searchDec(x, v, esq, mid - 1);
    else if (v[mid] > x) return searchDec(x, v, mid + 1, dre);
    return true;
}


bool search(int x, const vector<int>& v) {
    int j = buscaPosCim(v, 0, v.size()-1);
    if (v[j] < x) return false;
    return searchCre(x, v, 0, j) or searchDec(x, v, j+1, v.size()-1);
}

int main() {
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; ++i) cin >> v[i];
    int x;
    while (cin >> x) {
      cout << search(x, v) << endl;
    }
}
