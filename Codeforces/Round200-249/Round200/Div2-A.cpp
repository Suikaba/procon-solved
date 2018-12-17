#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    int ans = 0;
    string pre; cin >> pre;
    for(int i = 0; i < n - 1; ++i) {
        string s; cin >> s;
        if(pre != s) {
            ans += 1;
        }
        pre = s;
    }
    ans += 1;
    cout << ans << endl;
}
