
// http://codeforces.com/contest/550/problem/E

// 反省
// あんまりちゃんと取り組んでない．地道にやれば解けるやつですこれは．
// というかこれは解きたかった．条件が強い問題はどうせいい感じになる（ならないと解けないし）．

#include <bits/stdc++.h>
using namespace std;

constexpr int inf = 1e9;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    int pos = inf;
    const auto ok = [&] () {
        if(a.back() == 1) return false;
        if(n == 1 || a[n - 2] == 1) return true;
        for(int i = n - 3; i >= 0; --i) {
            if(a[i] == 0) {
                pos = i;
                return true;
            }
        }
        return false;
    }();
    if(!ok) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
        for(int i = 0; i < n; ++i) {
            if(i != 0 && i != pos + 1) cout << "->";
            if(i == pos) {
                cout << "(0->(";
            } else if(i == n - 2 && pos != inf) {
                cout << "0))";
            } else {
                cout << a[i];
            }
        }
    }
}
