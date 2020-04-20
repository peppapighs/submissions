#include <bits/stdc++.h>

#define long long long
#define iii tuple<int, int, int>
#define pii pair<long, long>
#define x first
#define y second

using namespace std;

const int N = 1e5+5;

int n, m, k;
vector<int> vec;
vector<pii> g[N];
vector<iii> E;

long d[N], par[N];

long solve1(int x1, int x2) {
    fill_n(d, N, 1e18), memset(par, 0, sizeof par);

    priority_queue<pii, vector<pii>, greater<pii> > Q;
    for(int x : vec) if(x != x1 && x != x2)
        Q.emplace(d[x] = 0, x), par[x] = x;
    while(!Q.empty()) {
        pii u = Q.top(); Q.pop();
        if(u.x != d[u.y]) continue;
        for(pii v : g[u.y]) if(u.x + v.y < d[v.x]) {
            Q.emplace(d[v.x] = u.x + v.y, v.x);
            par[v.x] = par[u.y];
        }
    } 
    long ret = 1e18;
    for(iii e : E) {
        int a, b, c; tie(a, b, c) = e;
        if(par[a] == par[b]) continue;
        if(d[a] + c + d[b] < ret)
            ret = d[a] + c + d[b];
    } 
    return ret;
}

void dijkstra(long d[], int src) {
    fill_n(d, N, 1e18);

    priority_queue<pii, vector<pii>, greater<pii> > Q;
    Q.emplace(d[src] = 0, src);
    while(!Q.empty()) {
        pii u = Q.top(); Q.pop();
        if(u.x != d[u.y]) continue;
        for(pii v : g[u.y]) if(u.x + v.y < d[v.x])
            Q.emplace(d[v.x] = u.x + v.y, v.x);
    }
}

long d1[N], d2[N];

long solve2(int x1, int x2) {
    vector<int> v1(vec), v2(vec);
    dijkstra(d1, x1), dijkstra(d2, x2);
    sort(v1.begin(), v1.end(), [&](int a, int b) { return d1[a] < d1[b]; });
    sort(v2.begin(), v2.end(), [&](int a, int b) { return d2[a] < d2[b]; });

    long ret = 1e18;
    for(int i = 0; i < min((int)v1.size(), 4); i++) for(int j = 0; j < min((int)v2.size(), 4); j++) {
        if(v1[i] == v2[j]) continue;
        if(v1[i] == x1 || v1[i] == x2) continue;
        if(v2[j] == x1 || v2[j] == x2) continue;
        ret = min(ret, d1[v1[i]] + d2[v2[j]]);
    }
    return ret;
}

int main() {
    fill_n(d, N, 1e18);

    scanf("%d %d %d", &n, &m, &k);
    for(int i = 1, a, b, c; i <= m; i++) {
        scanf("%d %d %d", &a, &b, &c);
        g[a].emplace_back(b, c), g[b].emplace_back(a, c);
        E.emplace_back(a, b, c);
    }
    priority_queue<pii, vector<pii>, greater<pii> > Q;
    for(int i = 1, a; i <= k; i++) {
        scanf("%d", &a);
        vec.emplace_back(a);
        Q.emplace(d[a] = 0, a), par[a] = a;
    }
    while(!Q.empty()) {
        pii u = Q.top(); Q.pop();
        if(u.x != d[u.y]) continue;
        for(pii v : g[u.y]) if(u.x + v.y < d[v.x]) {
            Q.emplace(d[v.x] = u.x + v.y, v.x);
            par[v.x] = par[u.y];
        }
    }
    long ret = 1e18, x1, x2;
    for(iii e : E) {
        int a, b, c; tie(a, b, c) = e;
        if(par[a] == par[b]) continue;
        if(d[a] + c + d[b] < ret)
            ret = d[a] + c + d[b], x1 = par[a], x2 = par[b];
    }
    printf("%lld\n", min(ret + solve1(x1, x2), solve2(x1, x2)));

    return 0;
}