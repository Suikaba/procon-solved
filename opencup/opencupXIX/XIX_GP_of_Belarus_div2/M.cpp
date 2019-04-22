#include <bits/stdc++.h>
using namespace std;

int main() {
    int cur; cin >> cur;
    cur--;
    vector<int> vis(20);
    string s;
    bool ng = false;
    if(0 <= cur && cur < 20) {
        vis[cur] = 1;
    } else {
        ng = true;
    }
    while(cin >> s) {
        if(s[0] == 'U') {
            cur += s[1] - '0';
        } else {
            cur -= s[1] - '0';
        }
        if(cur < 0 || 20 <= cur) {
            ng = true;
        } else {
            vis[cur] += 1;
            ng |= vis[cur] > 1;
        }
    }

    if(ng) {
        cout << "illegal" << endl;
    } else {
        vector<int> ans;
        for(int i = 0; i < 20; ++i) {
            if(!vis[i]) ans.push_back(i + 1);
        }

        if(ans.empty()) {
            cout << "none" << endl;
        } else {
            for(int i = 0; i < (int)ans.size(); ++i) {
                cout << ans[i] << " \n"[i + 1 == (int)ans.size()];
            }
        }
    }
}
