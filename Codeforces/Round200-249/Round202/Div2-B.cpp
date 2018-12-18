#include <bits/stdc++.h>
using namespace std;

int main() {
    int v; cin >> v;
    vector<int> a(9);
    for(int i = 0; i < 9; ++i) {
        cin >> a[i];
    }
    const int mi = *min_element(begin(a), end(a));
    const int keta = v / mi;
    if(keta == 0) {
        cout << -1 << endl;
        return 0;
    }

    string ans;
    for(int i = 0; i < keta; ++i) {
        for(int j = 8; j >= 0; --j) {
            if(v - a[j] >= 0 && (v - a[j]) / mi == keta - 1 - i) {
                ans += '1' + j;
                v -= a[j];
                break;
            }
        }
    }
    cout << ans << endl;
}
