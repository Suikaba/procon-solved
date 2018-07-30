
// http://codeforces.com/contest/1013/problem/A

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, x;
    cin >> n >> x;
    set<int> s;
    for(int i = 0; i < n; ++i) {
        int a; cin >> a;
        s.insert(a);
    }
    if(s.size() != n) {
        cout << 0 << endl;
    } else {
        bool one = false;
        for(auto& y : s) {
            if(s.count(y & x)) {
                one = true;
                break;
            }
        }
        if(one) {
            cout << 2 << endl;
            return 0;
        }
        set<int> t;
        for(auto y : s) {
            t.insert(y & x);
        }
        if(t.size() == n) {
            cout << 0 << endl;
        } else {
            cout << 2 << endl;
        }
    }
}
