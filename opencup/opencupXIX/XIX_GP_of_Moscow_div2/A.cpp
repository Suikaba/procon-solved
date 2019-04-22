#include <bits/stdc++.h>
using namespace std;

int main()
{
	int n;
	cin >> n;
	vector<int> a(n), x(n + 1);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	int y = -1;
	set<int> st;
	x[n] = -1;
	for (int i = n - 1; i >= 0; i--) {
		if (y == -1 && st.count(a[i])) y = a[i];
		st.insert(a[i]);
		x[i] = y;
	}
	int res = 0;
	for (int i = 0; i < n; ) {
		int l = i, val = a[i];
		while (i < n && a[i] == val) ++i;
		if (l != 0) res = max(res, x[i] - val);
		if (i != n) res = max(res, val - a[0]);
	}
	cout << res << endl;
	return 0;
}
