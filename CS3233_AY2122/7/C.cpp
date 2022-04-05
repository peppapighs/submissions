#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5 + 5;
const int INF = 1e9;

int T;
int n, k, ans;
int saf[N];
vector<int> g[N];

pii dfs(int u, int p) {
    pii ret(-INF, -INF);

    for(int &v : g[u]) if(v != p) {
        pii now = dfs(v, u);
        if(saf[u]) {
            ans = max(ans, ret.x + now.x + 1);
            ans = max(ans, ret.y + 1);
        } else {
            ans = max(ans, ret.x + now.y + 1);
            ans = max(ans, ret.y + now.x + 1);
        }
        if(now.x != -INF) ret.x = max(ret.x, now.x + 1);
        if(now.y != -INF) ret.y = max(ret.y, now.y + 1);
    }
    if(saf[u]) ret = pii(0, ret.x);

    return ret;
}

int main() {
    scanf("%d", &T);
    while(T--) {
        memset(saf, 0, sizeof saf);

        scanf("%d %d", &n, &k);
        for(int i = 0; i < n; i++) g[i].clear();
        for(int i = 0, a; i < k; i++) {
            scanf("%d", &a);
            saf[a] = 1;
        }
        for(int i = 0, a, b; i < n - 1; i++) {
            scanf("%d %d", &a, &b);
            g[a].emplace_back(b);
            g[b].emplace_back(a);
        }

        ans = 0;
        dfs(0, 0);
        if(ans) printf("%d\n", ans);
        else printf("-1\n");
    }

    return 0;
}