#include <bits/stdc++.h>
using namespace std;

typedef long double ld;

int main() {
    int n, a; cin >> n >> a;
    const ld loga = log10((long double)a);
    const ld logs[11] = {0.0L, log10(1.0L), log10(2.0L), log10(3.0L), log10(4.0L),
                         log10(5.0L), log10(6.0L), log10(7.0L), log10(8.0L), log10(9.0L), log10(10.0L)};

    vector<int> h(10), l(10);
    int low = a;
    for(int i = 1; i <= n; ++i) {
        const ld cur = loga * i;
        l[low] += 1;
        low = (low * a) % 10;
        const int keta = cur + 1;
        for(int hi = 0; hi < 10; ++hi) {
            if(keta - 1 + logs[hi] <= cur && cur < keta - 1 + logs[hi + 1]) {
                h[hi] += 1;
                break;
            }
        }
    }

    for(int i = 1; i <= 9; ++i) {
        cout << h[i] << " \n"[i == 9];
    }
    for(int i = 0; i < 10; ++i) {
        cout << l[i] << " \n"[i == 9];
    }
}
