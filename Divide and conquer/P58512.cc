#include <iostream>
using namespace std;

double exp(double per, int mid) {
	if (mid == 0) return 1;
	else {
		double x = exp(per, mid/2);
		if(mid%2 == 0) return x*x;
		else return x*x*per;
	}
}

int rates(int min, int max, double per, double m, double f) {
	if (min <= max) {
		int mid = (min + max)/2;
		double bank = exp(per, mid)*m;
		double prof = mid*f + m;
		if (prof > bank) return rates(mid+1, max, per, m, f);
		else if (prof < bank) return rates(min, mid-1,per,m,f);
		else return mid;
	}
	return min;
}

int main() {
	double m, f, per;
	while (cin >> m >> f >> per) {
		per = per/100 + 1;
		cout << rates(1, 10000000, per, m, f) << endl;
	}
}
