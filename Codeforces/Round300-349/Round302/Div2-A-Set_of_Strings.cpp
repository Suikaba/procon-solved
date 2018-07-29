
// http://codeforces.com/contest/544/problem/A

#include <bits/stdc++.h>
using namespace std;

int main() {
    int k;
    string s;
    cin >> k >> s;
    const int n = s.size();
    vector<bool> used(26);
    string now;
    vector<string> ans;
    for(int i = 0; i < n; ++i) {
        if(used[s[i] - 'a'] || (int)ans.size() == k - 1) {
            now += s[i];
            continue;
        }
        if(!now.empty()) {
            ans.push_back(now);
        }
        now = s[i];
        used[s[i] - 'a'] = true;
    }
    ans.push_back(now);

    if((int)ans.size() == k) {
        cout << "YES" << endl;
        for(auto& s : ans) {
            cout << s << endl;
        }
    } else {
        cout << "NO" << endl;
    }
}
