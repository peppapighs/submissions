#include "sort_weight.h"
#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e3 + 5;

int tree[N];
vector<vector<int>> perm;
vector<pii> op;

bool solve(vector<int> &now, int p, int sz) {
    if (now.size() > sz)
        return false;
    if (now.size() <= 1)
        return true;
    for (int i = 1; i <= op.size(); i++) {
        pii z = op[i - 1];
        vector<int> l, r;
        for (int idx : now) {
            if (perm[idx][z.x] < perm[idx][z.y])
                l.emplace_back(idx);
            else
                r.emplace_back(idx);
        }
        bool a = solve(l, p << 1, sz / 2);
        bool b = solve(r, p << 1 | 1, sz / 2);
        if (a && b) {
            tree[p] = i;
            return true;
        }
    }
    return false;
}

int main() {
    vector<int> vec = {0, 1, 2, 3, 4};
    do
        perm.emplace_back(vec);
    while (next_permutation(vec.begin(), vec.end()));

    for (int i = 0; i < 5; i++)
        for (int j = i + 1; j < 5; j++)
            op.emplace_back(i, j);

    vector<int> now(120);
    iota(now.begin(), now.end(), 0);
    solve(now, 1, 128);

    int T = get_case();
    while (T--) {
        sort_init();
        vector<int> now(120);
        iota(now.begin(), now.end(), 0);

        int p = 1;
        while (now.size() > 1) {
            vector<int> vec;
            pii z = op[tree[p] - 1];
            int ask = sort_weight(z.x, z.y);
            for (int idx : now) {
                if (ask == 1 && perm[idx][z.x] < perm[idx][z.y])
                    vec.emplace_back(idx);
                if (ask == -1 && perm[idx][z.x] > perm[idx][z.y])
                    vec.emplace_back(idx);
            }
            p = ask == 1 ? p << 1 : p << 1 | 1;
            swap(vec, now);
        }
        int ans[5];
        for (int i = 0; i < 5; i++)
            ans[i] = perm[now[i]][0];
        sort_answer(ans[0], ans[1], ans[2], ans[3], ans[4]);
    }

    return 0;
}