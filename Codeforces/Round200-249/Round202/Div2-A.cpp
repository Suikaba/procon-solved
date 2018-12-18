#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    int t25 = 0, t50 = 0;
    bool ans = true;
    for(int i = 0; i < n; ++i) {
        int a; cin >> a;
        if(a == 25) {
            t25 += 1;
        } else if(a == 50) {
            if(t25 == 0) ans = false;
            t25 -= 1;
            t50 += 1;
        } else {
            if(t50 != 0 && t25 != 0) {
                t50 -= 1, t25 -= 1;
            } else if(t25 >= 3) {
                t25 -= 3;
            } else {
                ans = false;
            }
        }
    }
    if(ans) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
}
