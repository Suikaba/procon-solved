#include <bits/stdc++.h>
using namespace std;

int main() {
    const int max_n = 1 << 10;
    vector<int> ts;
    for(int i = 1; i * (i + 1) / 2 < max_n; ++i) {
        ts.push_back(i * (i + 1) / 2);
    }
    vector<bool> ans(max_n);
    for(auto t1 : ts) {
        for(auto t2 : ts) {
            for(auto t3 : ts) {
                if(t1 + t2 + t3 < max_n) {
                    ans[t1 + t2 + t3] = true;
                }
            }
        }
    }
    int t; cin >> t;
    while(t--) {
        int k; cin >> k;
        cout << ans[k] << endl;
    }
}
