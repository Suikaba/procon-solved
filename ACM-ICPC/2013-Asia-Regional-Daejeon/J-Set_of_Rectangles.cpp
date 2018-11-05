#include <bits/stdc++.h>
using namespace std;

int main() {
    constexpr int max_l = 1000000;
    vector<vector<int>> tr;
    for(int x = 2; x * x <= max_l; ++x) {
        for(int y = 1; y < x; ++y) {
            const int a = 2 * x * y, b = x * x - y * y, c = x * x + y * y;
            if(a + b + c > max_l) break;
            if(__gcd(a, __gcd(b, c)) != 1) continue;
            tr.push_back({a, b, c});
            sort(begin(tr.back()), end(tr.back()));
        }
    }
    sort(begin(tr), end(tr),
         [] (vector<int> const& t1, vector<int> const& t2){
             return 2 * (t1[0] + t1[1]) < 2 * (t2[0] + t2[1]);
         });
    tr.erase(unique(begin(tr), end(tr)), end(tr));

    int T; cin >> T;
    while(T--) {
        int l; cin >> l;
        int ans = 0;
        while(l - 2 * (tr[ans][0] + tr[ans][1]) >= 0) {
            l -= 2 * (tr[ans][0] + tr[ans][1]);
            ans++;
        }
        cout << ans << endl;
    }
}
