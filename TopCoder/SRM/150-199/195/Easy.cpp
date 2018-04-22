#include <bits/stdc++.h>
using namespace std;

// SRM195 Div1 Easy

constexpr int inf = 1e9;

class FanFailure {
    const int max_value = 50000;
public:
    vector<int> getRange(vector<int> capacities, int min_cooling) {
        const int n = capacities.size();
        sort(begin(capacities), end(capacities));
        vector<int> mfs(max_value + 1, inf);
        mfs[0] = 0;
        for(auto cap : capacities) {
            auto nmfs = mfs;
            for(int i = 0; i + cap <= max_value; ++i) {
                nmfs[i + cap] = min(nmfs[i + cap], mfs[i] + 1);
            }
            mfs = move(nmfs);
        }

        int ans_mfs = inf, ans_mfc = 0;
        for(int i = min_cooling; i <= max_value; ++i) {
            ans_mfs = min(ans_mfs, mfs[i]);
        }
        ans_mfs = n - ans_mfs;

        int sum = 0;
        while(ans_mfc < n && sum < min_cooling) {
            sum += capacities[ans_mfc++];
        }
        ans_mfc = n - ans_mfc;

        return {ans_mfs, ans_mfc};
    }
};

//int main() {
//    FanFailure solve;
//    auto ans = solve.getRange({6, 8, 5, 7}, 22);
//    cout << ans[0] << ' ' << ans[1] << endl;
//}
