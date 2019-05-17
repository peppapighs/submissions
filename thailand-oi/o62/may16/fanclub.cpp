#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1<<18;

struct node {
    pii m[2];
    node() { }
    friend node operator+(const node &a, const node &b) {
        node ret;
        pii tmp[4];
        tmp[0] = a.m[0], tmp[1] = a.m[1], tmp[2] = b.m[0], tmp[3] = b.m[1];
        sort(tmp, tmp+4, greater<pii>());
        ret.m[0] = tmp[0], ret.m[1] = tmp[1];
        return ret;
    }
};

int n, m, st, en;
int par[N], dep[N], chk[N], pos[N];
node t1[N<<1], t2[N<<1];
vector<pii> g[N], path;

void dfs(int u, int p) {
    par[u] = p;
    for(pii v : g[u]) if(v.x != p) {
        dep[v.x] = dep[u] + v.y;
        dfs(v.x, u);
    }
}

int find_leaf(int u, int p) {
    int ans = dep[u];
    for(pii v : g[u]) if(v.x != p && !chk[v.x]) {
        dep[v.x] = dep[u] + v.y;
        ans = max(ans, find_leaf(v.x, u));
    }
    return ans;
}

void build(int p = 1, int l = 1, int r = path.size()) {
    if(l == r) {
        pii now = path[l-1];
        t1[p].m[0] = pii(dep[now.x] + now.y, now.x);
        t1[p].m[1] = pii(-1e9, -1e9);
        t2[p].m[0] = pii(dep[now.x] - now.y, now.x);
        t2[p].m[1] = pii(-1e9, -1e9); 
        return;
    }
    int mid = (l + r) >> 1;
    build(p<<1, l, mid), build(p<<1|1, mid+1, r);
    t1[p] = t1[p<<1] + t1[p<<1|1];
    t2[p] = t2[p<<1] + t2[p<<1|1];
}

node query1(int x, int y, int p = 1, int l = 1, int r = path.size()) {
    if(x > r || l > y) {
        node ret;
        ret.m[0] = ret.m[1] = pii(-1e9, -1e9);
        return ret;
    }
    if(x <= l && r <= y) return t1[p];
    int mid = (l + r) >> 1;
    return query1(x, y, p<<1, l, mid) + query1(x, y, p<<1|1, mid+1, r);
}

node query2(int x, int y, int p = 1, int l = 1, int r = path.size()) {
    if(x > r || l > y) {
        node ret;
        ret.m[0] = ret.m[1] = pii(-1e9, -1e9);
        return ret;
    }
    if(x <= l && r <= y) return t2[p];
    int mid = (l + r) >> 1;
    return query2(x, y, p<<1, l, mid) + query2(x, y, p<<1|1, mid+1, r);
}

int main() {
    scanf("%d %d %d %d", &n, &m, &st, &en);
    for(int i = 1, a, b, c; i < n; i++) {
        scanf("%d %d %d", &a, &b, &c);
        g[a].emplace_back(b, c);
        g[b].emplace_back(a, c);
    } 

    dfs(st, 0);
    for(int i = en; i; i = par[i]) {
        path.emplace_back(i, dep[i]);
        chk[i] = true;
    }
    reverse(path.begin(), path.end());
    for(int i = 1; i <= path.size(); i++) pos[path[i-1].x] = i;

    memset(dep, 0, sizeof dep);
    for(pii p : path) dep[p.x] = find_leaf(p.x, p.x);

    build();
    
    for(int q = 1, a, b; q <= m; q++) {
        scanf("%d %d", &a, &b);
        if(pos[a] > pos[b]) swap(a, b);

        node q1 = query1(pos[a], pos[b]);
        node q2 = query2(pos[a], pos[b]);

        int ans = 0;
        for(int i = 0; i < 2; i++) for(int j = 0; j < 2; j++)
            if(q1.m[i].y != q2.m[j].y) ans = max(ans, q1.m[i].x + q2.m[j].x);

        printf("%d\n", ans);
    }

    return 0;
}