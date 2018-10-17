#include <bits/stdc++.h>
using namespace std;

constexpr double inf = 1e9;
constexpr double gratio = (std::sqrt(5)+1)/2.0;

// 下に凸な関数Fの区間[lb, ub]における最小となる点を求める．
// cnt は 200 ぐらいなら十分な精度になってた．
template <typename F>
double golden_section_search(F f, double lb, double ub, int cnt) {
    double x1 = (ub-lb)/(gratio+1) + lb,
        x2 = (ub-lb)*gratio/(gratio+1) + lb;
    double v1 = f(x1), v2 = f(x2);
    for(int i=0; i<cnt; ++i) {
        if(v1 < v2) {
            ub = x2;
            x2 = x1;
            v2 = v1;
            x1 = (ub-lb)/(gratio+1) + lb;
            v1 = f(x1);
        } else {
            lb = x1;
            x1 = x2;
            v1 = v2;
            x2 = (ub-lb)*gratio/(gratio+1) + lb;
            v2 = f(x2);
        }
    }
    return (lb+ub)/2;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cout << fixed << setprecision(10);
    int n; cin >> n;
    vector<double> a(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    auto f = [&] (double x) {
        vector<double> sum(n + 1);
        double min_s = 0, max_s = 0;
        double res = 0;
        for(int i = 0; i < n; ++i) {
            sum[i + 1] = sum[i] + a[i] - x;
            res = max({res, abs(sum[i + 1] - max_s), abs(sum[i + 1] - min_s)});
            min_s = min(min_s, sum[i + 1]);
            max_s = max(max_s, sum[i + 1]);
        }
        return res;
    };
    const auto opti = golden_section_search(f, -10000, 10000, 100);
    cout << f(opti) << endl;
}
