#include "trilib.h"
#include <bits/stdc++.h>

using namespace std;

int n;

void convex_hull(vector<int> &v) {
    vector<int> ans;
    for(int x : v) {
        while(ans.size() > 1 && !is_clockwise(ans[ans.size() - 2], ans.back(), x))
            ans.pop_back();
        ans.emplace_back(x);
    }
    v = ans;
}

int main() {
    n = get_n();
    vector<int> l, r;
    for(int i = 3; i <= n; i++) {
        if(!is_clockwise(1, 2, i)) l.emplace_back(i);
        else r.emplace_back(i);
    }
    sort(l.begin(), l.end(), [&](int &a, int &b) { return is_clockwise(1, a, b); });
    sort(r.begin(), r.end(), [&](int &a, int &b) { return is_clockwise(1, a, b); });
    l.emplace_back(2), r.emplace_back(1);
    convex_hull(l), convex_hull(r);

    for(int x : r) l.emplace_back(x);
    convex_hull(l);

    deque<int> ans(l.begin(), l.end());
    while(true) {
        bool valid = true;
        if(!is_clockwise(ans[ans.size() - 2], ans.back(), ans.front()))
            ans.pop_back(), valid = false;
        if(is_clockwise(ans[1], ans[0], ans.back()))
            ans.pop_front(), valid = false;
        if(valid) break;
    }

    give_answer(ans.size());

    return 0;
}