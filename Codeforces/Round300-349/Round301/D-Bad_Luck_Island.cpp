
// http://codeforces.com/contest/540/problem/D

// 反省点
// nCr のサイズをミスった．注意するか，余裕あるなら大きめに取るようにすればいい．
// tuple 使ったのはコード長的に反省？方針は特に反省する点はない．

#include <bits/stdc++.h>
using namespace std;

using ld = long double;

template<typename T>
std::vector<T> table(int n, T v) { return std::vector<T>(n, v); }

template <class... Args>
auto table(int n, Args... args) {
    auto val = table(args...);
    return std::vector<decltype(val)>(n, std::move(val));
}

int main() {
    int r, s, p;
    cin >> r >> s >> p;
    vector<vector<ld>> nCr(1 << 9, vector<ld>(1 << 9));
    for(int i = 1; i < 1 << 9; ++i) {
        for(int j = 0; j <= i; ++j) {
            if(i == j || j == 0) nCr[i][j] = 1;
            else nCr[i][j] += nCr[i - 1][j] + nCr[i - 1][j - 1];
        }
    }
    auto dp = table(r + 1, s + 1, p + 1, make_tuple(0.0L, 0.0L, 0.0L));
    auto mul = [] (tuple<ld, ld, ld> v, ld p) {
        get<0>(v) *= p;
        get<1>(v) *= p;
        get<2>(v) *= p;
        return v;
    };
    auto add = [] (tuple<ld, ld, ld>& v, tuple<ld, ld, ld> const& v2) {
        get<0>(v) += get<0>(v2);
        get<1>(v) += get<1>(v2);
        get<2>(v) += get<2>(v2);
    };
    function<tuple<ld, ld, ld>(int, int, int)> rec = [&] (int r, int s, int p) {
        if(r < 0 || s < 0 || p < 0) {
            return make_tuple(0.0L, 0.0L, 0.0L);
        }
        if((r == 0 && s == 0) || (s == 0 && p == 0) || (p == 0 && r == 0)) {
            return dp[r][s][p] = make_tuple(r > 0, s > 0, p > 0);
        }
        if(dp[r][s][p] != make_tuple(0.0L, 0.0L, 0.0L)) {
            return dp[r][s][p];
        }
        auto& res = dp[r][s][p];
        const auto tot = nCr[r + s + p][2];
        const auto self = (nCr[r][2] + nCr[s][2] + nCr[p][2]) / tot;
        add(res, mul(rec(r, s - 1, p), r * s / tot / (1 - self)));
        add(res, mul(rec(r, s, p - 1), s * p / tot / (1 - self)));
        add(res, mul(rec(r - 1, s, p), r * p / tot / (1 - self)));

        return res;
    };

    auto ans = rec(r, s, p);
    cout << fixed << setprecision(12);
    cout << get<0>(ans) << ' ' << get<1>(ans) << ' ' << get<2>(ans) << endl;
}
