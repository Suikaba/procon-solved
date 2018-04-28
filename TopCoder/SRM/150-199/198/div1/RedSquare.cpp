// BEGIN CUT HERE
// END CUT HERE

#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

class RedSquare {
public:
    int countTheEmptyReds(int maxRank, int maxFile, vector <int> rank, vector <int> file) {
        set<pii> piece;
        const int n = rank.size();
        for(int i = 0; i < n; ++i) {
            piece.emplace(rank[i], file[i]);
        }

        int ans = 0;
        for(int i = 1; i <= maxRank; ++i) {
            for(int j = 1; j <= maxFile; ++j) {
                const int dist = i - 1 + maxFile - j;
                if((dist & 1) && !piece.count(make_pair(i, j))) {
                    ans += 1;
                }
            }
        }

        return ans;
    }
};
