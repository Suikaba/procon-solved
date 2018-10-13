//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1617

#include <bits/stdc++.h>
using namespace std;

int main() {
    string s1;
    while(cin >> s1, s1 != ".") {
        string s2; cin >> s2;
        const int n = s1.size(), m = s2.size();
        int cnt = 0;
        bool in_str = false;
        int i = 0, j = 0;
        while(i < n && j < m) {
            if(s1[i] != s2[j]) {
                if(!in_str) {
                    cnt = 2;
                    break;
                }
                cnt += 1;
                while(i < n && s1[i] != '\"') i++;
                while(j < m && s2[j] != '\"') j++;
                i = i + 1; j = j + 1;
            } else {
                in_str ^= s1[i] == '\"';
                i++, j++;
            }
        }
        if(i != n || j != m || cnt >= 2) {
            cout << "DIFFERENT" << endl;
        } else if(cnt == 1) {
            cout << "CLOSE" << endl;
        } else {
            cout << "IDENTICAL" << endl;
        }
    }
}
