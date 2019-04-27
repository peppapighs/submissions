#include "game.h"
#include <bits/stdc++.h>

using namespace std;

const int N = 1505;

int n;
int com[N], cnt[N][N], sz[N];

void initialize(int _n) {
    n = _n;
    fill_n(sz, N, 1), iota(com, com+n, 0);
}

int hasEdge(int u, int v) {
    u = com[u], v = com[v];
    if(sz[u] * sz[v] - 1 == cnt[u][v]) {
        for(int i = 0; i < n; i++) cnt[u][i] += cnt[v][i];
        for(int i = 0; i < n; i++) cnt[i][u] += cnt[i][v];
        for(int i = 0; i < n; i++) if(com[i] == v) com[i] = u;
        sz[u] += sz[v];
        return 1;
    } else ++cnt[u][v], ++cnt[v][u];
    return 0;
}