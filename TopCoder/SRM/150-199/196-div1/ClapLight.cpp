// BEGIN CUT HERE
// END CUT HERE

#include <bits/stdc++.h>
using namespace std;

class ClapLight {
public:
    int threshold(vector <int> background) {
        const int n = background.size();
        int ans = 0;
        while(++ans <= 1001) {
            vector<int> low_sig(n);
            for(int i = 0; i < n; ++i) {
                low_sig[i] = background[i] < ans;
            }
            const int low_sz = count(begin(low_sig), end(low_sig), 1);
            if(low_sz * 2 <= n) {
                continue;
            }

            bool f = false;
            for(int i = 3; i < n; ++i) {
                f |= low_sig[i - 3] == 1 && low_sig[i - 2] == 0 && low_sig[i - 1] == 0 && low_sig[i] == 1;
            }
            if(!f) break;
        }

        return ans;
    }
};
