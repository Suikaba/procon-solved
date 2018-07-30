
// http://codeforces.com/contest/545/problem/A

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> ans;
    for(int i = 0; i < n; ++i) {
        bool check = true;
        for(int j = 0; j < n; ++j) {
            int a; cin >> a;
            check &= a == -1 || a == 0 || a == 2;
        }
        if(check) ans.push_back(i);
    }
    cout << ans.size() << endl;
    for(int i = 0; i < (int)ans.size(); ++i) {
        cout << ans[i] + 1 << " \n"[i + 1 == (int)ans.size()];
    }
}
