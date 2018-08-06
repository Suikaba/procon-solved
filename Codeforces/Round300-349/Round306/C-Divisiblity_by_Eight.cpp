#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    const int n = s.size();
    string ans = [&] () {
        string res;
        for(int i = 0; i < n; ++i) {
            if((s[i] - '0') % 8 == 0) {
                res = s[i];
                return res;
            }
            for(int j = i + 1; j < n; ++j) {
                const int t2 = 10 * (s[i] - '0') + (s[j] - '0');
                if(s[i] != '0' && t2 % 8 == 0) {
                    res += s[i];
                    res += s[j];
                    return res;
                }
                for(int k = j + 1; k < n; ++k) {
                    const int t3 = 100 * (s[i] - '0') + 10 * (s[j] - '0') + (s[k] - '0');
                    if(s[i] != '0' && s[j] != '0' && t3 % 8 == 0) {
                        res += s[i];
                        res += s[j];
                        res += s[k];
                        return res;
                    }
                }
            }
        }
        return res;
    }();
    if(ans.empty()) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
        cout << ans << endl;
    }
}
