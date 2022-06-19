#include "Boblib.h"
#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e3 + 50;

static int n, rep;
static int is_node[N], id[N];
static vector<int> g[N];

void Bob(int n, int m, int A[], int B[]) {
    for (int i = 0; i < m; i++) {
        g[A[i]].emplace_back(B[i]);
        g[B[i]].emplace_back(A[i]);
    }

    for (int i = 0; i < n; i++)
        if (g[i].size() == 1 && g[g[i][0]].size() == n - 11) {
            rep = g[i][0];
            for (int x : g[rep])
                is_node[x] = 1;
            break;
        }
    int now = rep, pre = rep;
    for (int i = 0; i < n; i++)
        if (i != rep && !is_node[i] && g[i].size() <= g[now].size())
            now = i, pre = i;
    for (int i = 9; ~i; i--) {
        for (int x : g[now])
            if (is_node[x])
                id[x] += 1 << i;
        for (int x : g[now])
            if (!is_node[x] && x != pre) {
                pre = now, now = x;
                break;
            }
    }

    vector<pii> E;
    for (int i = 0; i < m; i++)
        if (is_node[A[i]] && is_node[B[i]])
            E.emplace_back(id[A[i]], id[B[i]]);
    InitMap(n - 12, (int)E.size());
    for (pii p : E)
        MakeMap(p.x, p.y);
}
