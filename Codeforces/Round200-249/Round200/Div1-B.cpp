#include <bits/stdc++.h>
using namespace std;

int main() {
    string s; cin >> s;
    const int n = s.size();
    if(n & 1) {
        cout << "No" << endl;
        return 0;
    }

    list<int> ls;
    char pre = '*';
    int cnt = 0;
    for(int i = 0; i < n; ++i) {
        if(pre == s[i]) {
            cnt += 1;
        } else {
            ls.push_back(cnt);
            cnt = 1;
        }
        pre = s[i];
    }
    ls.push_back(cnt);

    for(auto it = ls.begin(); it != ls.end();) {
        if(*it >= 2) {
            const bool b = *it & 1;
            it = ls.erase(it);
            if(b) {
                ls.insert(it, 1);
            } else if(it != begin(ls)) {
                *it += *prev(it);
                ls.erase(prev(it));
            }
        } else {
            ++it;
        }
    }

    if(ls.empty()) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
}
