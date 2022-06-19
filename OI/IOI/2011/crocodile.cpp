#include "crocodile.h"
#include <bits/stdc++.h>

#define long long long
#define pii pair<long, long>
#define x first
#define y second

using namespace std;

const int N = 1e5 + 5;

int chk[N];
vector<pii> g[N];

int travel_plan(int n, int m, int r[][2], int l[], int k, int p[]) {
    for (int i = 0; i < m; i++) {
        int a = r[i][0], b = r[i][1], c = l[i];
        g[a].emplace_back(b, c);
        g[b].emplace_back(a, c);
    }
    priority_queue<pii, vector<pii>, greater<pii>> Q;
    for (int i = 0; i < k; i++) {
        chk[p[i]] = 1;
        Q.emplace(0, p[i]);
    }
    while (!Q.empty()) {
        pii now = Q.top();
        Q.pop();
        ++chk[now.y];
        if (chk[now.y] != 2)
            continue;
        if (!now.y)
            return now.x;
        for (pii v : g[now.y])
            if (chk[v.x] < 2)
                Q.emplace(now.x + v.y, v.x);
    }
}