#include <bits/stdc++.h>
using namespace std;

int main() {
    int m; cin >> m;
    vector<int> c(m);
    vector<int> sum(m + 1);
    for(int i = 0; i < m; ++i) {
        cin >> c[i];
        sum[i + 1] = sum[i] + c[i];
    }
    int x, y; cin >> x >> y;

    int ans = 0;
    for(int i = 1; i < m; ++i) {
        if(x <= sum[i] && sum[i] <= y && x <= sum.back() - sum[i] && sum.back() - sum[i] <= y) {
            ans = i + 1;
        }
    }
    cout << ans << endl;
}
