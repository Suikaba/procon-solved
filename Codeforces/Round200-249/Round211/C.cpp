#include <bits/stdc++.h>
using namespace std;

int main() {
    string s; cin >> s;
    const int n = s.size();
    string ans;
    for(int i = 0; i < n; ++i) {
        const int l = ans.size();
        if((int)l >= 2 && ans[l - 1] == s[i] && ans[l - 2] == ans[l - 1]) continue;
        if((int)l >= 3 && ans[l - 1] == s[i] && ans[l - 2] == ans[l - 3]) continue;
        ans += s[i];
    }
    cout << ans << endl;
}
