#include <bits/stdc++.h>
using namespace std;

using card_type = pair<int, char>;

const string nums = "23456789TJQKA";
const string suit = "SHDC";

card_type convert(string s) {
    auto res = make_pair(0, s[0]);
    if(s[1] == 'A') res.first = 14;
    else if(s[1] == 'J') res.first = 11;
    else if(s[1] == 'Q') res.first = 12;
    else if(s[1] == 'K') res.first = 13;
    else if(s[1] == 'T') res.first = 10;
    else res.first = s[1] - '0';
    return res;
}

pair<int, vector<int>> strength(vector<card_type> hand) {
    sort(begin(hand), end(hand), greater<>{});
    bool fls = true, straight = true;
    vector<int> ns;
    map<int, int> cnt;
    for(int i = 0; i < 5; ++i) {
        auto c = hand[i];
        fls &= c.second == hand[0].second;
        straight &= i == 4 || hand[i].first == hand[i + 1].first + 1;
        ns.push_back(c.first);
        cnt[c.first] += 1;
    }
    straight |= ns == vector<int>{14, 5, 4, 3, 2};
    if(fls && ns == vector<int>{14, 13, 12, 11, 10}) return make_pair(100, vector<int>{}); // royal straight flush
    if(fls && straight) {
        if(ns == vector<int>{14, 5, 4, 3, 2}) return make_pair(90, vector<int>{1, 5});
        return make_pair(90, vector<int>{1, ns[0]});
    }

    vector<pair<int, int>> cs;
    for(auto& p : cnt) cs.emplace_back(p.second, p.first);
    sort(begin(cs), end(cs), greater<>{});
    vector<int> ms;
    for(auto p : cs) ms.push_back(p.second);

    // four of a kind
    if(cs[0].first == 4) return make_pair(80, ms);
    // full house
    if(cs[0].first == 3 && cs[1].first == 2) return make_pair(70, ms);
    // flush
    if(fls) return make_pair(60, ns);
    // straight
    if(ns == vector<int>{14, 5, 4, 3, 2}) return make_pair(50, vector<int>{1, 5});
    if(straight) return make_pair(50, vector<int>{1, ns[0]});
    // three of kind
    if(cs[0].first == 3) return make_pair(40, ms);
    // two pair
    if(cs[0].first == 2 && cs[1].first == 2) return make_pair(30, ms);
    // one pair
    if(cs[0].first == 2) return make_pair(20, ms);
    // no pair
    return make_pair(0, ns);
}

int main() {
    string s;
    while(cin >> s, s != "#") {
        set<card_type> remain;
        for(auto n : nums) {
            for(auto st : suit) {
                string t; t += st; t += n;
                remain.insert(convert(t));
            }
        }
        remain.erase(convert(s));
        vector<vector<card_type>> hands(2);
        hands[0].push_back(convert(s));
        cin >> s;
        hands[0].push_back(convert(s));
        remain.erase(convert(s));
        for(int i = 0; i < 2; ++i) {
            cin >> s;
            hands[1].push_back(convert(s));
            remain.erase(convert(s));
        }
        for(int i = 0; i < 3; ++i) {
            cin >> s;
            hands[0].push_back(convert(s));
            hands[1].push_back(convert(s));
            remain.erase(convert(s));
        }

        double ans = 0;
        for(auto r1 : remain) {
            for(auto r2 : remain) {
                if(r1 >= r2) continue;
                auto hs = hands;
                for(int i = 0; i < 2; ++i) {
                    hs[i].push_back(r1);
                    hs[i].push_back(r2);
                }
                vector<int> choice(7, 1);
                choice[0] = choice[1] = 0;
                auto str1 = make_pair(-1, vector<int>{}), str2 = make_pair(-1, vector<int>{});
                do {
                    vector<vector<card_type>> use(2);
                    for(int i = 0; i < 7; ++i) {
                        if(choice[i]) use[0].push_back(hs[0][i]);
                        if(choice[i]) use[1].push_back(hs[1][i]);
                    }
                    str1 = max(str1, strength(use[0]));
                    str2 = max(str2, strength(use[1]));
                } while(next_permutation(begin(choice), end(choice)));
                ans += str1 > str2;
            }
        }

        ans /= 990;
        cout << fixed << setprecision(10) << ans << endl;
    }
}
