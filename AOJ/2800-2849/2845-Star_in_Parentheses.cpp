#include <bits/stdc++.h>
using namespace std;

int main() {
    string s; cin >> s;
    const int n = s.size();

    int ans = 0;
    for(int l = 0; l < n; ++l) {
        for(int r = l + 2; r < n; ++r) {
            if(s[l] != '(' || s[r] != ')') continue;
            bool ok = true, found = false;
            int cnt = 0;
            for(int i = l + 1; i <= r - 1; ++i) {
                if(s[i] == '(') cnt += 1;
                if(s[i] == ')') cnt -= 1;
                if(s[i] == '*') found = true;
                ok &= cnt >= 0;
            }
            ans += ok && cnt == 0 && found;
        }
    }

    cout << ans << endl;
}
