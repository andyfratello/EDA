#include <iostream>
#include <set>
#include <algorithm>
using namespace std;

struct compare {
	bool operator()(const string& a, const string& b) {
		if (a.length() == b.length()) return a < b;
		return a.length() < b.length();
	}
};

int main() {
	set <string> has;
	set <string, compare> had;
	string input;
	int game = 1;
	bool quit = 0, first = true;

	cin >> input;
	while (not quit) {
		while (not (input == "END" or input == "QUIT")) {
			if (has.count(input)) {
				has.erase(input);
				had.insert(input);
			} else {
				has.insert(input);
				had.erase(input);
			}
			cin >> input;
		}

		if (not first) cout << endl;
		first = false;

		cout << "GAME #" << game << endl << "HAS:" << endl;
		for (string elem : has) cout << elem << endl;
		cout << endl << "HAD:" << endl;
		for (string elem : had) cout << elem << endl;

		++game;
		has.erase(has.begin(), has.end());
		had.erase(had.begin(), had.end());

		if (input == "QUIT") quit = 1;
		else cin >> input;
	}
}
/*
struct sizestring {
    bool operator() (const string& a, const string& b) {
        if (a.size() != b.size()) return a.size() < b.size();
        return a < b;
    }
};

typedef set<string>::iterator iter_has;
typedef set<string, sizestring>::iterator iter_had;

int main() {
    string w;
    int count = 1;
    iter_has it1;
    iter_had it2;
    bool first = true;
    while(w != "QUIT") {
        set<string> has;
        set<string, sizestring> had;
        while (cin >> w and w != "END" and w != "QUIT") {
            it1 = has.find(w);
            if (it1 == has.end()) has.insert(w);
            else {
                has.erase(it1);
                had.insert(w);
            }
        }
        if (first) first = false;
        else cout << endl;
        cout << "GAME #" << count << endl;
        cout << "HAS:" << endl;
        for (it1 = has.begin(); it1 != has.end(); ++it1) cout << *it1 << endl; 
        cout << endl;
        cout << "HAD:" << endl;
        for (it2 = had.begin(); it2 != had.end(); ++it2) cout << *it2 << endl; 
        ++count;
        has.erase(has.begin(), has.end());
		had.erase(had.begin(), had.end());
    }
}*/
