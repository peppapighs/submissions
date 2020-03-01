#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y  second

using namespace std;

const int N = 1e5+5;

int n, m, k;
int in[N], out[N], pos[N], hv[N], sz[N];
vector<pii> g[N];

int dfs(int u, int p) {
    static int idx = 0;

    pii ret(0, -1);
    pos[in[u] = ++idx] = u, sz[u] = 1;
    for(pii v : g[u]) if(v.x != p) {
        int z = dfs(v.x, u);
        sz[u] += z, ret = max(ret, pii(z, v.x));
    }
    hv[u] = ret.y, out[u] = idx;
    return sz[u];
}

vector<int> vec[N], ans;
int pol_sz[N], cnt[N], cur_ans;

void add(int u, bool b) {
    for(int x : vec[u]) {
        if(b) {
            if(cnt[x] == 0) ++cur_ans;
            ++cnt[x];
            if(cnt[x] == pol_sz[x]) --cur_ans;
        } else {
            if(cnt[x] == pol_sz[x]) ++cur_ans;
            --cnt[x];
            if(cnt[x] == 0) --cur_ans;
        }
    }
}

void sack(int u, int p, bool keep, int id) {
    for(pii v : g[u]) if(v.x != p && v.x != hv[u])
        sack(v.x, u, 0, v.y);
    for(pii v : g[u]) if(v.x == hv[u])
        sack(v.x, u, 1, v.y);
    for(pii v : g[u]) if(v.x != p && v.x != hv[u])
        for(int i = in[v.x]; i <= out[v.x]; i++) 
            add(pos[i], 1);
    add(u, 1);
    if(cur_ans >= k) ans.emplace_back(id);
    if(!keep) for(int i = in[u]; i <= out[u]; i++)
        add(pos[i], 0);
}

int main() {
    scanf("%d %d %d", &n, &m, &k);
    for(int i = 1, a, b; i < n; i++) {
        scanf("%d %d", &a, &b);
        g[a].emplace_back(b, i);
        g[b].emplace_back(a, i);
    }
    dfs(1, 0);
    for(int i = 1, a; i <= m; i++) {
        scanf("%d", &a);
        pol_sz[i] = a;
        for(int j = 1, b; j <= a; j++) {
            scanf("%d", &b);
            vec[b].emplace_back(i);
        }
    }
    sack(1, 0, 1, -1);

    sort(ans.begin(), ans.end());
    printf("%d\n", ans.size());
    for(int x : ans) printf("%d ", x);
    printf("\n");

    return 0;
}