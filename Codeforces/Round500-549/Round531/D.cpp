#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    string s; cin >> s;
    int c0 = 0, c1 = 0, c2 = 0;
    for(int i = 0; i < n; ++i) {
        c0 += (s[i] == '0');
        c1 += (s[i] == '1');
        c2 += (s[i] == '2');
    }

    const int t = n / 3;
    for(int i = 0; i < n && c0 < t; ++i) {
        if(s[i] == '1' && c1 > t) {
            c1 -= 1;
            s[i] = '0';
            c0 += 1;
        } else if(s[i] == '2' && c2 > t) {
            c2 -= 1;
            s[i] = '0';
            c0 += 1;
        }
    }
    for(int i = n - 1; i >= 0 && c2 < t; --i) {
        if(s[i] == '1' && c1 > t) {
            c1--;
            s[i] = '2';
            c2 += 1;
        }
        if(s[i] == '0' && c0 > t) {
            c0--;
            s[i] = '2';
            c2 += 1;
        }
    }
    for(int i = 0; i < n && c1 < t; ++i) {
        if(s[i] == '2' && c2 > t) {
            s[i] = '1';
            c2--;
            c1 += 1;
        }
    }
    for(int i = n - 1; i >= 0 && c1 < t; --i) {
        if(s[i] == '0' && c0 > t) {
            s[i] = '1';
            c0--;
            c1 += 1;
        }
    }

    cout << s << endl;
}
