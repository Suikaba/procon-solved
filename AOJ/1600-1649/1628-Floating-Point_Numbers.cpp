#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ll n;
    while(cin >> n, n) {
        ll a = 1LL << 52;
        for(int i = 51; i >= 0; --i) {
            char b; cin >> b;
            a |= (ll)(b == '1') << i;
        }

        ll ex = 0, sig = a;
        while(n > 0 && a != 0) {
            const ll cnt = min(n, ((1LL << 53) - sig + a - 1) / a);
            sig += a * cnt;
            while(sig >= 1LL << 53) {
                ex += 1;
                sig >>= 1;
                a >>= 1;
            }
            n -= cnt;
        }

        cout << bitset<64>((ex << 52) | (sig & ((1LL << 52) - 1))) << endl;
    }
}
