#include <bits/stdc++.h>
using namespace std;
using ld = long double;

const ld pi = acos(-1.);

ld common_area(int d, ld r) {
	const ld theta = acos(max((ld)0.0, min((ld)1.0, d / (r * 2))));
	return r * r * theta * 2 - r * d * sin(theta);
}

int main() {
	cout << fixed << setprecision(10);
	int n, r; cin >> n >> r;
	vector<int> a(n);
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}
	sort(begin(a), end(a));

	ld ans = n * r * r * pi;
	for (int i = 1; i < n; i++) {
		if (a[i] - a[i - 1] < r * 2) {
			ans -= common_area(a[i] - a[i - 1], r);
		}
	}

	cout << ans << endl;
}