#include <bits/stdc++.h>

#define long long long
#define pii pair<long, long>
#define x first
#define y second
#define iii tuple<long, long, long>

using namespace std;

const int N = 1e5+5;

int n, m, q;
iii d[N][2];
long ap[105][105];
vector<pii> g[N];
vector<int> coord;

int get(int x) { return lower_bound(coord.begin(), coord.end(), x) - coord.begin() + 1; }

void dfs(int u, int p, int id, int ptr, long len) {
    if(coord[get(u)-1] == u) return void(ap[id][get(u)] = min(ap[id][get(u)], len));
    if(!get<0>(d[u][0])) d[u][0] = iii(id, ptr, len);
    else d[u][1] = iii(id, ptr, len);
    for(pii v : g[u]) if(v.x != p) dfs(v.x, u, id, ptr, len + v.y);
}

int main() {
    fill_n(ap[0], 105 * 105, 1e12);
    scanf("%d %d %d", &n, &m, &q);
    for(int i = 1, a, b, c; i <= m; i++) {
        scanf("%d %d %d", &a, &b, &c);
        g[a].emplace_back(b, c), g[b].emplace_back(a, c);
    }
    for(int i = 1; i <= n; i++) if(g[i].size() > 2) coord.emplace_back(i);
    if(coord.empty()) coord.emplace_back(1);
    sort(coord.begin(), coord.end());

    int ptr = 0;
    for(int u : coord) {
        ap[get(u)][get(u)] = 0;
        d[u][0] = iii(get(u), ++ptr, 0);
        d[u][1] = iii(-1, -1, 0);
        for(pii v : g[u]) dfs(v.x, u, get(u), ++ptr, v.y);
    }
    for(int k = 1; k <= coord.size(); k++)
        for(int i = 1; i <= coord.size(); i++)
            for(int j = 1; j <= coord.size(); j++)
                ap[i][j] = min(ap[i][j], ap[i][k] + ap[k][j]);

    for(int t = 1, a, b; t <= q; t++) {
        scanf("%d %d", &a, &b);
        long ret = 1e18;
        for(int i = 0; i < 2; i++) for(int j = 0; j < 2; j++) {
            int ida, pa, idb, pb;
            long la, lb;
            tie(ida, pa, la) = d[a][i], tie(idb, pb, lb) = d[b][j];
            if(ida == -1 || idb == -1 || !ida || !idb) continue;
            if(pa == pb) ret = min(ret, abs(la - lb));
            else ret = min(ret, la + ap[ida][idb] + lb);
        }
        printf("%lld\n", ret);
    }

    return 0;
}