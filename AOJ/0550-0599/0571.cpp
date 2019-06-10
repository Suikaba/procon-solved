#include <bits/stdc++.h>
using namespace std;

int main() {
    string s; cin >> s;
    const int n = s.size();

    int ans = 0;
    int J = -1, O = -1, I = -1;
    for(int i = 0; i < n; ++i) {
        if(s[i] == 'J') {
            J = (J == -1 || O != -1 ? 1 : J + 1);
            O = I = -1;
        } else if(s[i] == 'O') {
            if(J == -1) continue;
            if(I != -1) {
                J = -1, O = -1, I = -1;
                continue;
            } else {
                O = (O == -1 ? 1 : O + 1);
                I = -1;
            }
        } else {
            if(O == -1) {
                J = -1;
                continue;
            }
            I = (I == -1 ? 1 : I + 1);
            if(O <= J && O == I) {
                ans = max(ans, I);
            }
        }
    }

    cout << ans << endl;
}
