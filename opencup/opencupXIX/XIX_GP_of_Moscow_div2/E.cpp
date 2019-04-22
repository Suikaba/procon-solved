#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
	ll n;
	cin >> n;
	int t = 1, cnt = 0;
	while (t < n) t <<= 1, ++cnt;
	cout << cnt << endl;
	int x;
	cin >> x;
	if (x) {
		int y;
		while (cin >> y, y != 0) {
			cout << 1 << endl;
		}
	}
	else {
		int y = 1e9;
		cout << y << endl;
		cin >> y;
		assert(0 < y);
		cout << -1 << endl;
	}
	return 0;
}
