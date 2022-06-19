#include "sorting.h"
#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 2e5 + 5;

int findSwapPairs(int n, int s[], int m, int x[], int y[], int p[], int q[]) {
    auto solve = [&](int k) {
        vector<int> v(s, s + n), pos(n);
        vector<pii> ret;
        for (int i = 0; i < k; i++)
            swap(v[x[i]], v[y[i]]);
        for (int i = 0; i < n; i++)
            pos[v[i]] = i;
        for (int i = 0; i < n; i++)
            if (v[i] != i) {
                ret.emplace_back(v[i], i);
                int now = v[i];
                swap(v[i], v[pos[i]]);
                swap(pos[now], pos[i]);
            }
        return ret;
    };

    int l = 0, r = m;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (solve(mid).size() <= mid)
            r = mid;
        else
            l = mid + 1;
    }

    vector<pii> ans = solve(r);
    vector<int> pos(n);
    for (int i = 0; i < n; i++)
        pos[s[i]] = i;
    for (int i = 0; i < r; i++) {
        swap(pos[s[x[i]]], pos[s[y[i]]]);
        swap(s[x[i]], s[y[i]]);

        if (i < ans.size()) {
            int a, b;
            tie(a, b) = ans[i];
            p[i] = pos[a], q[i] = pos[b];
            swap(s[pos[a]], s[pos[b]]);
            swap(pos[a], pos[b]);
        } else
            p[i] = q[i] = 0;
    }

    return r;
}