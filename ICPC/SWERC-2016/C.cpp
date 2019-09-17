#include <bits/stdc++.h>
using namespace std;

int main() {
    int d;
    while(cin >> d) {
        int r, t; cin >> r >> t;
        int ans = 0;
        for(int rm = 0; rm <= r; ++rm) {
            int c1 = r - rm, c2 = t + rm;
            int y1 = 4, y2 = 3;
            while(c1 > 0) {
                c1 -= y1;
                y1 += 1;
            }
            while(c2 > 0) {
                c2 -= y2;
                y2 += 1;
            }
            if(c1 == 0 && c2 == 0 && abs(y1 - y2) == d) {
                ans = rm;
                break;
            }
        }
        cout << ans << endl;
    }
}