#include <bits/stdc++.h>
using namespace std;

constexpr int inf = 1e9;

int main() {
    int hp_y, atk_y, def_y; cin >> hp_y >> atk_y >> def_y;
    int hp_m, atk_m, def_m; cin >> hp_m >> atk_m >> def_m;
    int h, a, d; cin >> h >> a >> d;

    int ans = inf;
    for(int buy_a = 0; buy_a <= 200; ++buy_a) {
        for(int buy_d = 0; buy_d <= 200; ++buy_d) {
            int hp = hp_y, atk = buy_a + atk_y, def = def_y + buy_d;
            if(atk - def_m <= 0) continue;
            int cost = buy_a * a + buy_d * d;
            int hp_e = hp_m;
            while(hp_e > 0) {
                hp -= max(0, atk_m - def);
                hp_e -= atk - def_m;
                if(hp <= 0) {
                    cost += (1 - hp) * h;
                    hp = 1;
                }
            }
            ans = min(ans, cost);
        }
    }

    cout << ans << endl;
}
