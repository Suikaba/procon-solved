
// @author kazuma8128

#include <bits/stdc++.h>
using namespace std;

template<int MOD>
class mod_int {
	unsigned x;
public:
	mod_int() : x(0) { }
	mod_int(int sig) { int sigt = sig % MOD; if (sigt < 0) sigt += MOD; x = sigt; }
	mod_int(long long sig) { int sigt = sig % MOD; if (sigt < 0) sigt += MOD; x = sigt; }
	int get() const { return (int)x; }

	mod_int &operator+=(mod_int that) { if ((x += that.x) >= MOD) x -= MOD; return *this; }
	mod_int &operator-=(mod_int that) { if ((x += MOD - that.x) >= MOD) x -= MOD; return *this; }
	mod_int &operator*=(mod_int that) { x = (unsigned long long)x * that.x % MOD; return *this; }
	mod_int &operator/=(mod_int that) { return *this *= that.inverse(); }

	mod_int operator+(mod_int that) const { return mod_int(*this) += that; }
	mod_int operator-(mod_int that) const { return mod_int(*this) -= that; }
	mod_int operator*(mod_int that) const { return mod_int(*this) *= that; }
	mod_int operator/(mod_int that) const { return mod_int(*this) /= that; }

	bool operator==(const mod_int& that) const { return x == that.x; }

	mod_int inverse() const {
		long long a = x, b = MOD, u = 1, v = 0;
		while (b) {
			long long t = a / b;
			a -= t * b; swap(a, b);
			u -= t * v; swap(u, v);
		}
		return mod_int(u);
	}
};

template<int MOD>
istream& operator >> (istream& is, mod_int<MOD>& val) {
	long long x;
	is >> x; val = x;
	return is;
}

template<int MOD>
ostream& operator << (ostream& os, const mod_int<MOD>& val) {
	os << val.get();
	return os;
}

const int mod = 1e9 + 7;
using mint = mod_int<mod>;

const int B = 30;

mint pps[B][B][4];

int main()
{
	ios::sync_with_stdio(false), cin.tie(0);
	int n, X, Y;
	cin >> n >> X >> Y;
	mint P = mint(X) / mint(Y);
	mint Q = mint(1) - P;
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	for (int i = 0; i < B; i++) {
		for (int j = 0; j < B; j++) {
			pps[i][j][0] = 1;
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < B; j++) {
			for (int k = 0; k <= j; k++) {
				if (a[i] & ((1 << j) | (1 << k))) {
					int flag = (((a[i] >> j) & 1) << 1) | ((a[i] >> k) & 1);
					mint tmp[4];
					for (int b = 0; b < 4; b++) {
						tmp[b] = pps[j][k][b];
						pps[j][k][b] = 0;
					}
					for (int b = 0; b < 4; b++) {
						pps[j][k][b] += tmp[b] * Q;
						pps[j][k][b ^ flag] += tmp[b] * P;
					}
				}
			}
		}
	}
	mint res = 0, d1 = 1;
	for (int i = 0; i < B; i++) {
		mint d2 = d1;
		for (int j = 0; j < B; j++) {
			if (i >= j) {
				res += pps[i][j][3] * d2;
			}
			else {
				res += pps[j][i][3] * d2;
			}
			d2 *= 2;
		}
		d1 *= 2;
	}
	cout << res << endl;
	return 0;
}

