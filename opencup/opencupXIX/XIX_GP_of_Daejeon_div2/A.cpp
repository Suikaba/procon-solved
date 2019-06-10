#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    string s; cin >> s;

    int ans = 1, cur = 0;
    char pre = 'V';
    for(int i = 0; i < n; ++i) {
        if(s[i] == 'V') {
            ans = max(ans, cur);
            cur = 0;
        } else {
            if(s[i] != pre) {
                ans = max(ans, ++cur);
            } else {
                ans = max(ans, cur);
                cur = 1;
            }
        }
        pre = s[i];
    }

    cout << ans << endl;
}
