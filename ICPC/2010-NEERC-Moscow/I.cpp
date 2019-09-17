#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

struct interests_log {
    int user_id, category_id, create_time, heuristic_ctr;
    interests_log() {}
    interests_log(int a, int b, int c, int d) : user_id(a), category_id(b), create_time(c), heuristic_ctr(d) {}
    bool operator<(const interests_log& e) const {
        return create_time < e.create_time;
    }
};

struct events_log {
    int user_id, category_id, adv_id, show_time, click_flag;
    events_log(int d, int e, int a, int b, int c) : user_id(d), category_id(e), adv_id(a), show_time(b), click_flag(c) {}
    bool operator<(const events_log& e) const {
        return show_time < e.show_time;
    }
};

struct result {
    int user, cate, create, heu, adv, show, click;
    result(int a, int b, int c, int d, int e, int f, int g) : user(a), cate(b), create(c), heu(d), adv(e), show(f), click(g) {}
    bool operator<(const result& r) const {
        return make_tuple(heu, user, cate, create, adv, show) < make_tuple(r.heu, r.user, r.cate, r.create, r.adv, r.show);
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int n, m; cin >> n >> m;
    vector<interests_log> ilog;
    vector<events_log> elog;
    for(int i = 0; i < n; ++i) {
        int user_id, category_id, create_time, heuristic_ctr;
        cin >> user_id >> category_id >> create_time >> heuristic_ctr;
        ilog.emplace_back(user_id, category_id, create_time, heuristic_ctr);
    }
    for(int i = 0; i < m; ++i) {
        int user_id, category_id, adv_id, show_time, click_flag;
        cin >> user_id >> category_id >> adv_id >> show_time >> click_flag;
        elog.emplace_back(user_id, category_id, adv_id, show_time, click_flag);
    }
    sort(begin(ilog), end(ilog));
    sort(begin(elog), end(elog));

    int itr1 = 0, itr2 = 0;
    map<pii, interests_log> memo;
    vector<result> ans; // (heur, user, cate, create, adv, show)
    while(itr2 < m) {
        if(itr1 < n && ilog[itr1].create_time < elog[itr2].show_time) {
            memo[make_pair(ilog[itr1].user_id, ilog[itr1].category_id)] = ilog[itr1];
            itr1 += 1;
        } else {
            const auto& el = elog[itr2];
            if(memo.count(make_pair(el.user_id, el.category_id))) {
                const auto& il = memo[make_pair(el.user_id, el.category_id)];
                ans.emplace_back(el.user_id, el.category_id, il.create_time, il.heuristic_ctr, el.adv_id, el.show_time, el.click_flag);
            }
            itr2 += 1;
        }
    }
    sort(begin(ans), end(ans));

    cout << ans.size() << endl;
    for(auto const& r : ans) {
        cout << r.user << " " << r.cate << " " << r.create << " " << r.heu << " " << r.adv << " " << r.show << " " << r.click << "\n";
    }
}
