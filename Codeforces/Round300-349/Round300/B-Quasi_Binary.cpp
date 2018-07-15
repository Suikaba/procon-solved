
// http://codeforces.com/contest/538/problem/B

#include <bits/stdc++.h>
using namespace std;

constexpr int inf = 1e9;

int main() {
    string s;
    cin >> s;
    vector<int> ans;
    while(stoi(s) != 0) {
        char mi = '9';
        const int n = s.size();
        for(int i = 0; i < n; ++i) {
            if(s[i] == '0') continue;
            mi = min(mi, s[i]);
        }
        string x;
        for(int i = 0; i < n; ++i) {
            if(s[i] == '0') x += '0';
            else {
                x += '1';
                s[i] -= mi - '0';
            }
        }
        for(char i = '0'; i < mi; ++i) {
            ans.push_back(stoi(x));
        }
        s = to_string(stoi(s));
    }

    sort(begin(ans), end(ans));
    const int n = ans.size();
    cout << n << endl;
    for(int i = 0; i < n; ++i) {
        cout << ans[i] << " \n"[i + 1 == n];
    }
}
