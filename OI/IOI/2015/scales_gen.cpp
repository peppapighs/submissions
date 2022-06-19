#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5 + 5;

int tree[N];
vector<vector<int>> perm;
vector<pair<int, vector<int>>> op;

void scales_init() {
    vector<int> gen = {1, 2, 3, 4, 5, 6};
    do
        perm.emplace_back(gen);
    while (next_permutation(gen.begin(), gen.end()));

    for (int b = 0; b < 1 << 6; b++)
        if (__builtin_popcount(b) == 3) {
            vector<int> now;
            for (int i = 0; i < 6; i++)
                if (b >> i & 1)
                    now.emplace_back(i);
            for (int i = 1; i <= 3; i++)
                op.emplace_back(i, now);
            for (int i = 0; i < 6; i++)
                if (!(b >> i & 1)) {
                    vector<int> tmp = now;
                    tmp.emplace_back(i);
                    op.emplace_back(4, tmp);
                }
        }
}

int last;

bool solve(vector<int> vec, int p, int sz) {
    if (vec.size() > sz)
        return false;
    if (vec.size() <= 1)
        return true;

    last = max(last, p);
    for (int t = 0; t < op.size(); t++) {
        int T = op[t].x;
        vector<int> ask = op[t].y;
        vector<int> ans[6];

        for (int idx : vec) {
            vector<pii> now;
            for (int i = 0; i < 3; i++)
                now.emplace_back(perm[idx][ask[i]], ask[i]);
            sort(now.begin(), now.end());

            if (T == 1)
                ans[now[2].y].emplace_back(idx);
            if (T == 2)
                ans[now[0].y].emplace_back(idx);
            if (T == 3)
                ans[now[1].y].emplace_back(idx);
            if (T == 4) {
                bool valid = false;
                for (int i = 0; i < 3; i++)
                    if (now[i].x > perm[idx][ask[3]]) {
                        ans[now[i].y].emplace_back(idx);
                        valid = true;
                        break;
                    }
                if (!valid)
                    ans[now[0].y].emplace_back(idx);
            }
        }
        bool valid = true;
        int step = 0;
        for (int i = 0; i < 6; i++)
            if (ans[i].size() > sz / 3)
                valid = false;
        if (valid)
            for (int i = 0; i < 6; i++)
                if (ans[i].size()) {
                    ++step;
                    bool now = solve(ans[i], p * 3 + step, sz / 3);
                    if (!now) {
                        valid = false;
                        break;
                    }
                }
        if (valid) {
            tree[p] = t;
            return true;
        }
    }
    return false;
}

int main() {
    scales_init();
    vector<int> vec(720);
    iota(vec.begin(), vec.end(), 0);
    solve(vec, 0, 729);

    for (int i = 0; i <= last; i++)
        printf("%d, ", tree[i]);
    printf("\n");

    return 0;
}