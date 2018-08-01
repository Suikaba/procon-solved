
// http://codeforces.com/contest/1015/problem/B

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    string s, t;
    cin >> n >> s >> t;
    vector<int> ans;
    for(int i = 0; i < n; ++i) {
        if(s[i] == t[i]) continue;
        for(int j = i + 1; j < n; ++j) {
            if(s[j] == t[i]) {
                for(int k = j - 1; k >= i; --k) {
                    ans.push_back(k + 1);
                    swap(s[k], s[k + 1]);
                }
                break;
            }
        }
    }
    if(s == t) {
        cout << ans.size() << endl;
        for(int i = 0; i < (int)ans.size(); ++i) {
            cout << ans[i] << " \n"[i + 1 == (int)ans.size()];
        }
    } else {
        cout << -1 << endl;
    }
}
