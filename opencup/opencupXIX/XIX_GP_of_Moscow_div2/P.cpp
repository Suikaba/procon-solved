#include <bits/stdc++.h>
using namespace std;

int main() {
    string p, q; cin >> p >> q;
    if(p != "0" && (q == "0" || p == q)) {
        reverse(begin(p), end(p));
        for(int i = 0; i < (int)p.size(); ++i) {
            if(p[i] == '0') {
                p[i] = '9';
            } else {
                p[i] -= 1;
                break;
            }
        }
        while(p.back() == '0' && p.size() != 1u) p.pop_back();
        reverse(begin(p), end(p));
        cout << p << endl;
    } else {
        cout << 0 << endl;
    }
}