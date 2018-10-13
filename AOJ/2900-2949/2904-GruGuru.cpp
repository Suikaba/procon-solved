// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2904

#include <bits/stdc++.h>
using namespace std;

int main() {
    string s; cin >> s;
    const int n = s.size();
    int ans = 0;
    bool ng = false;
    int dir = 0;
    for(int i = 0; i < n; ++i) {
        if(s[i] == 'R') {
            dir = (dir + 1) % 4;
            if(dir == 0) {
                ans += !ng;
                ng = false;
            }
        } else {
            dir = (dir + 3) % 4;
            if(dir == 3) {
                ng = true;
            }
            if(dir == 0) {
                ng = false;
            }
        }
    }
    cout << ans << endl;
}
