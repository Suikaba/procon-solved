
// http://codeforces.com/contest/569/problem/B

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    vector<int> a(n);
    vector<bool> used(n + 1);
    set<int> s;
    for(int i = 1; i <= n; ++i) {
        s.insert(i);
    }
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
        s.erase(a[i]);
    }
    for(int i = 0; i < n; ++i) {
        if(a[i] < 0 || n < a[i] || used[a[i]]) {
            a[i] = *s.begin();
            used[*s.begin()] = true;
            s.erase(s.begin());
        } else {
            used[a[i]] = true;
        }
    }
    for(int i = 0; i < n; ++i) {
        cout << a[i] << " \n"[i + 1 == n];
    }
}
