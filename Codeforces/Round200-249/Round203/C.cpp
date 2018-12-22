#include <bits/stdc++.h>
using namespace std;

struct point {
    int x, y;
    point(int x_, int y_) : x(x_), y(y_) {}

    bool operator<(const point& that) const {
        return abs(x) + abs(y) < abs(that.x) + abs(that.y);
    }
};

int main() {
    int n; cin >> n;
    vector<point> ps;
    for(int i = 0; i < n; ++i) {
        int x, y; cin >> x >> y;
        ps.emplace_back(x, y);
    }
    sort(begin(ps), end(ps));

    int step = 0;
    for(int i = 0; i < n; ++i) {
        step += 2;
        if(ps[i].x != 0) {
            step += 2;
        }
        if(ps[i].y != 0) {
            step += 2;
        }
    }

    cout << step << endl;
    for(int i = 0; i < n; ++i) {
        if(ps[i].x != 0) {
            cout << "1 " << abs(ps[i].x) << " " << (ps[i].x < 0 ? 'L' : 'R') << "\n";
        }
        if(ps[i].y != 0) {
            cout << "1 " << abs(ps[i].y) << " " << (ps[i].y < 0 ? 'D' : 'U') << "\n";
        }
        cout << "2" << "\n";
        if(ps[i].y != 0) {
            cout << "1 " << abs(ps[i].y) << " " << (ps[i].y < 0 ? 'U' : 'D') << "\n";
        }
        if(ps[i].x != 0) {
            cout << "1 " << abs(ps[i].x) << " " << (ps[i].x < 0 ? 'R' : 'L') << "\n";
        }
        cout << "3" << "\n";
    }
}
