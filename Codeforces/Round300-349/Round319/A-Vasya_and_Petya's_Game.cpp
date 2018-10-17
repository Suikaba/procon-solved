// http://codeforces.com/contest/576/problem/A

#include<bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    if(n == 1) {
        cout << 0 << endl;
        return 0;
    }
    set<int> ans;
    for(int i = 2; i <= n; ++i) {
        int tmp = i;
        for(int x = 2; x <= tmp; ++x) {
            if(tmp % x == 0) {
                int y = x;
                while(tmp % x == 0) {
                    ans.insert(y);
                    y *= x;
                    tmp /= x;
                }
            }
        }
        if(tmp > 1) {
            ans.insert(tmp);
        }
    }
    cout << ans.size() << endl;
    for(auto x : ans) {
        cout << x << endl;
    }
}
