#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ll a, b; cin >> a >> b;
    vector<string> ans;
    while(a != b) {
        const ll g = __gcd(a, b);
        a /= g, b /= g;
        if((a & 1) && (b & 1)) {
            if(a < b) {
                b += a;
                ans.push_back("B+=A");
            } else {
                a += b;
                ans.push_back("A+=B");
            }
        } else {
            if(a & 1) {
                a += a;
                ans.push_back("A+=A");
            } else {
                b += b;
                ans.push_back("B+=B");
            }
        }
    }

    cout << ans.size() << endl;
    for(auto const& s : ans) {
        cout << s << endl;
    }
}
