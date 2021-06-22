#include <iostream>
#include <map>
#include <vector>
#include <queue>
using namespace std;

typedef vector<vector<int>> Grafo;

void ordenacion_top(const Grafo& tareas, map<string,int>& pos_tareas, const vector<string>& nombres, vector<int>& ge, queue<string>& orden) {
    int n = tareas.size();
    priority_queue<string, vector<string>, greater<string>> pq;
    for (int i = 0; i < n; ++i) {
        if (ge[i] == 0) pq.push(nombres[i]);
    }
    while (not pq.empty()) {
        string s = pq.top();
        pq.pop();
        orden.push(s);
        int u = pos_tareas[s];
        /* for (int i = 0; i < tareas[u].size(); ++i) {
            int v = tareas[u][i];
        } */
        for (int v : tareas[u]) {
            if (--ge[v] == 0) pq.push(nombres[v]);
        }
    }
}

int main() {
    int n;
    while (cin >> n) {
        map<string, int> pos_tareas;
        vector<string> nombres (n);
        for (int i = 0; i < n; ++i) {
            string s;
            cin >> s;
            nombres[i] = s;
            pos_tareas.insert({s, i});
        }
        int m;
        cin >> m;
        Grafo tareas(n);
        vector<int> ge(n, 0);
        for (int i = 0; i < m; ++i) {
            string x, y;
            cin >> x >> y;
            // map<string, int>::iterator it = pos_tareas.find(x);
            // tareas[it->second]
            tareas[pos_tareas[x]].push_back(pos_tareas[y]);
            ++ge[pos_tareas[y]];
        }
        queue<string> orden;
        ordenacion_top(tareas, pos_tareas, nombres, ge, orden);
        if (orden.size() == nombres.size()) {
            while (not orden.empty()) {
                cout << orden.front();
                orden.pop();
            }
            cout << endl;
        } else cout << "NO VALID ORDERING" << endl;
    }
}
