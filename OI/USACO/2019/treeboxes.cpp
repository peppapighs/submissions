#include "grader.h"
#include <bits/stdc++.h>

using namespace std;

const int N = 1e5+5;

int par[N][18], dep[N];
int sz[N], X[N], Y[N];
vector<int> g[N];

int pre_process(int u, int p) { 
    par[u][0] = p, dep[u] = dep[p] + 1, sz[u] = 1;
    for(int i = 1; i <= 17; i++) par[u][i] = par[par[u][i-1]][i-1];
    for(int v : g[u]) if(v != p) sz[u] += pre_process(v, u);
    return sz[u];
}

void gen_tree(int u, int p, int x, int y) {
    setFarmLocation(u, x, y);
    X[u] = x, Y[u] = y;
    int nx = x - sz[u], ny = y;
    for(int v : g[u]) if(v != p) {
        nx += sz[v];
        gen_tree(v, u, nx, ny);
        ny -= sz[v];
    }
}

void addRoad(int a, int b) {
    g[a].emplace_back(b);
    g[b].emplace_back(a);
}

void buildFarms() {
    pre_process(0, 0);
    gen_tree(0, 0, sz[0], sz[0]);
}

void notifyFJ(int a, int b) {
    if(dep[a] < dep[b]) swap(a, b);
    int x = a, y = b;
    for(int i = 17; ~i; i--) if(dep[par[x][i]] >= dep[y]) x = par[x][i];
    if(x == y) addBox(X[a], Y[a], X[b], Y[b]);
    else {
        for(int i = 17; ~i; i--) if(par[x][i] != par[y][i]) x = par[x][i], y = par[y][i];
        addBox(X[a], Y[a], X[x], Y[x]);
        addBox(X[b], Y[b], X[par[x][0]], Y[par[x][0]]);
    }
}