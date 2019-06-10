#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, t;
    while(cin >> n >> t, n) {
        vector<int> m(n), l(n), k(n);
        for(int i = 0; i < n; ++i) {
            cin >> m[i] >> l[i] >> k[i];
        }

        auto check = [&] (int num) {
            vector<int> restore(t + 1);
            list<int> ls;
            for(int i = 0; i < n; ++i) ls.push_back(i);
            int remain = num;
            for(int i = 0; i <= t; ++i) {
                remain += restore[i];
                auto it = ls.begin();
                while(remain > 0 && it != ls.end()) {
                    const int idx = *it;
                    if(i % (l[idx] + k[idx]) <= l[idx]) {
                        --remain;
                        if(i + m[idx] > t) return false;
                        restore[i + m[idx]] += 1;
                        it = ls.erase(it);
                    } else {
                        ++it;
                    }
                }
            }
            return ls.empty();
        };
        for(int i = 1; i <= n; ++i) {
            if(check(i)) {
                cout << i << endl;
                break;
            }
        }
    }
}
