#include <bits/stdc++.h>

#define long long long
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 2e5 + 5;
const int M = 2.5e4 + 5;
const int B = 500;

int n, re, q, init;

struct node {
    int d, l, r;
    node(int d, int l, int r) : d(d), l(l), r(r) {}
};

vector<node> vec;

int newleaf(int d) {
    vec.emplace_back(d, -1, -1);
    return (int)vec.size() - 1;
}

int newpar(int l, int r) {
    vec.emplace_back(0, l, r);
    return (int)vec.size() - 1;
}

int build(int l = 1, int r = re) {
    if(l == r) return newleaf(0);
    int mid = (l + r) >> 1;
    return newpar(build(l, mid), build(mid + 1, r));
}

int update(int x, int k, int p, int l = 1, int r = re) {
    if(l == r) return newleaf(vec[p].d + k);
    int mid = (l + r) >> 1;
    if(x <= mid) return newpar(update(x, k, vec[p].l, l, mid), vec[p].r);
    else return newpar(vec[p].l, update(x, k, vec[p].r, mid + 1, r));
}

int get_val(int x, int p, int l = 1, int r = re) {
    if(l == r) return vec[p].d;
    int mid = (l + r) >> 1;
    if(x <= mid) return get_val(x, vec[p].l, l, mid);
    else return get_val(x, vec[p].r, mid + 1, r);
}

int R[N], ver[N], hv[N], in[N], out[N], pos[N];
int id[M], inv[M], cnt[M], ptr;
long sum[B][B];
vector<int> g[N], emp[M], euler[M];

int preprocess(int u) {
    static int idx = 0;

    pos[in[u] = ++idx] = u;
    int sz = 1; pii ret(0, -1);
    for(int v : g[u]) {
        int z = preprocess(v);
        sz += z, ret = max(ret, pii(z, v));
    }
    hv[u] = ret.y, out[u] = idx;
    return sz;
}

void sack(int u, bool save) {
    ver[u] = update(R[u], 1, ver[u]);
    for(int v : g[u]) if(v != hv[u]) {
        ver[v] = ver[u];
        sack(v, 0);
    }
    if(hv[u] != -1) {
        ver[hv[u]] = ver[u];
        sack(hv[u], 1);
    }
    for(int v : g[u]) if(v != hv[u])
        for(int i = in[v]; i <= out[v]; i++)
            ++cnt[R[pos[i]]];
    ++cnt[R[u]];
    if(id[R[u]]) for(int i = 1; i <= ptr; i++)
        sum[id[R[u]]][i] += cnt[inv[i]];
    if(!save) for(int i = in[u]; i <= out[u]; i++)
        --cnt[R[pos[i]]];
}

int main() {
    scanf("%d %d %d %d", &n, &re, &q, R + 1);
    emp[R[1]].emplace_back(1);
    for(int i = 2, p; i <= n; i++) {
        scanf("%d %d", &p, R + i);
        g[p].emplace_back(i);
        emp[R[i]].emplace_back(i);
    }
    for(int i = 1; i <= re; i++) if((int)emp[i].size() >= B)
        inv[id[i] = ++ptr] = i;
    init = build();
    fill_n(ver, N, init);

    preprocess(1), sack(1, 1);
    for(int i = 1; i <= n; i++) euler[R[pos[i]]].emplace_back(i);

    for(int i = 1, a, b; i <= q; i++) {
        scanf("%d %d", &a, &b);
        if(id[a] && id[b]) printf("%lld\n", sum[id[a]][id[b]]);
        else {
            long ans = 0;
            if(!id[a])
                for(int u : emp[a])
                    ans += upper_bound(euler[b].begin(), euler[b].end(), out[u])
                        - lower_bound(euler[b].begin(), euler[b].end(), in[u]);
            else for(int u : emp[b]) ans += get_val(a, ver[u]);
            printf("%lld\n", ans);
        }
        fflush(stdout);
    }

    return 0;
}