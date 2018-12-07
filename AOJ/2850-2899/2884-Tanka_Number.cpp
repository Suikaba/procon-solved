#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ll n;
    while(cin >> n, n) {
        ll keta = 2, cnt = 0;
        while(cnt + 9 * 9 * ((1LL << (keta - 1)) - 1) < n) {
            cnt += 9 * 9 * ((1LL << (keta - 1)) - 1);
            keta += 1;
        }
        cnt = n - cnt;

        string ans;
        function<void(int, int, int)> solve = [&] (int d, int a, int b) {
            if(d == keta) return;
            if(a == -1) {
                for(a = 1; a <= 9; ++a) {
                    if(cnt > 9 * ((1LL << (keta - 1)) - 1)) {
                        cnt -= 9 * ((1LL << (keta - 1)) - 1);
                        continue;
                    }
                    break;
                }
                ans += '0' + a;
                solve(d + 1, a, b);
            } else if(b == -1) {
                for(b = 0; b <= 9; ++b) {
                    if(a != b) {
                        if(cnt > (1LL << (keta - d - 1))) {
                            cnt -= 1LL << (keta - d - 1);
                            continue;
                        }
                        break;
                    } else {
                        if(cnt > 9 * ((1LL << (keta - d - 1)) - 1)) {
                            cnt -= 9 * ((1LL << (keta - d - 1)) - 1);
                            continue;
                        }
                        break;
                    }
                }
                ans += '0' + b;
                if(a == b) solve(d + 1, a, -1);
                else       solve(d + 1, a, b);
            } else {
                const int ma = max(a, b), mi = min(a, b);
                if(cnt > (1LL << (keta - d - 1))) {
                    cnt -= 1LL << (keta - d - 1);
                    ans += '0' + ma;
                } else {
                    ans += '0' + mi;
                }
                solve(d + 1, a, b);
            }
        };
        solve(0, -1, -1);

        cout << ans << endl;
    }
}
