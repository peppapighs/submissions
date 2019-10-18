#include "icc.h"
#include <bits/stdc++.h>

using namespace std;

const int N = 105;

int n;
int par[N], a[N], b[N], c[N];
vector<int> C[N];

int find(int x) { while(x != par[x]) x = par[x]; return x; }

void unite(int a, int b) {
    a = find(a), b = find(b);
    if(C[a].size() > C[b].size()) swap(a, b);
    for(int x : C[a]) C[b].emplace_back(x);
    par[a] = b;
}

int solve(int pa, int pb, int a[], int b[]) {
    int l = 0, r = pa-1;
    while(l < r) {
        int mid = (l + r) >> 1;
        int pc = 0;
        for(int i = 0; i <= mid; i++) c[pc++] = a[i];
        if(query(pc, pb, c, b)) r = mid;
        else l = mid + 1;
    }
    return a[r];
}

void run(int _n) {
    n = _n;
    iota(par, par+N, 0);
    for(int i = 1; i <= n; i++) C[i].emplace_back(i);
    for(int road = 1; road < n; road++) {
        vector<int> vec;
        for(int i = 1; i <= n; i++) if(par[i] == i) vec.emplace_back(i);
        for(int bit = 0; bit <= 7; bit++) {
            int pa = 0, pb = 0;
            for(int i = 0; i < vec.size(); i++) {
                if(i >> bit & 1) for(int x : C[vec[i]]) a[pa++] = x;
                else for(int x : C[vec[i]]) b[pb++] = x;
            }
            if(pa == 0 || pb == 0) continue;
            if(query(pa, pb, a, b)) {
                int u = solve(pa, pb, a, b);
                int v = solve(pb, pa, b, a);
                unite(u, v), setRoad(u, v);
                break;
            }
        }
    }
}