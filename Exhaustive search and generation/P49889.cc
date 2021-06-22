#include <iostream>
#include <vector>
using namespace std;

void convoc(string& sol, const string& cons, const string& voc, vector<bool>& visCon, vector<bool>& visVoc, int n, int i) {
    if (i == 2*n) cout << sol << endl;
    else {
        if (i%2 == 0) {
            for (int j = 0; j < n; ++j) {
                if (not visCon[j]) {
                    visCon[j] = true;
                    sol[i] = cons[j];
                    convoc(sol, cons, voc, visCon, visVoc, n, i+1);
                    visCon[j] = false;
                }
            }
        } else {
            for (int j = 0; j < n; ++j) {
                if (not visVoc[j]) {
                    visVoc[j] = true;
                    sol[i] = voc[j];
                    convoc(sol, cons, voc, visCon, visVoc, n, i+1);
                    visVoc[j] = false;
                }
            }
        }
    }
}

int main() {
    int n;
    cin >> n;
    string cons, voc;
    cin >> cons >> voc;
    vector<bool> visCon(n, false);
    vector<bool> visVoc(n, false);
    string sol(2*n, ' ');
    convoc(sol, cons, voc, visCon, visVoc, n, 0);
}
