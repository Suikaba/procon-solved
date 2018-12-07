#include <bits/stdc++.h>
using namespace std;

int main() {
    int s; cin >> s;
    s *= 4;
    vector<int> vs;
    for(int i = 1; i <= s; ++i) {
        if(s % i != 0) continue;
        vs.push_back(i);
    }
    const int n = vs.size();
    int ans = 0;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            for(int k = 0; k < n; ++k) {
                const int w = vs[i], x = vs[j], y = vs[k];
                if(s % (w * x * y) != 0) continue;
                const int z = s / w / x / y;
                const int a = (w - x + 1) / 2, b = (w + x - 1) / 2;
                const int c = (y - z + 1) / 2, d = (y + z - 1) / 2;
                if(a <= 0 || b <= 0 || c <= 0 || d <= 0) continue;
                ans += s == (b + a) * (b - a + 1) * (d + c) * (d - c + 1);
            }
        }
    }

    cout << ans << endl;
}
