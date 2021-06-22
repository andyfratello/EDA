#include <iostream>
#include <string>
#include <sstream>
#include <set>
using namespace std;

int main() {
    string st;
    while(getline(cin, st)) {
        set<int> s; //un set per cada linea
        int x;
        istringstream ss(st);
        while (ss >> x) 
            s.insert(x); //insertar elements de la linea
        if (s.empty()) cout << 0 << endl;
        else {
            bool senar = true;
            set<int>::iterator it = s.begin();
            if ((*it)%2 == 0) senar = false;

            int contador = 1; //l'element inicial ja vist

            for (it = s.begin(); it != s.end(); ++it) {
                bool sen2 = true;
                if ((*it)%2 == 0) sen2 = false;

                if (senar != sen2) ++contador;
                senar = sen2; //iterem sobre els elements
            }
            cout << contador << endl;

        }
    }
 
}
