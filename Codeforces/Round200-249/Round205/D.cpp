#include <bits/stdc++.h>
using namespace std;

int main() {
    string s; cin >> s;
    const int n = s.size();
    int ans = 0, cnt = 0;
    int st = 0;
    while(st < n && s[st] == 'F') {
        st += 1;
        cnt += 1;
    }
    for(int i = st; i < n; ++i) {
        if(s[i] == 'F') {
            ans = max(i - cnt, ans + 1);
            cnt += 1;
        }
    }

    cout << ans << endl;
}
