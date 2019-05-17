#include <bits/stdc++.h>

using namespace std;

const int N = 3e5+5;

int n, k, cc, in1[N], in2[N];
int pre[N], low[N], chk[N], comp[N];
vector<int> g[N];
char s[N][35];

void tarjan(int u) {
    static int idx = 0;
    static stack<int> S;
    pre[u] = low[u] = ++idx, chk[u] = true;
    S.emplace(u);
    for(int v : g[u]) {
        if(!pre[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if(chk[v]) low[u] = min(low[u], pre[v]);
    }
    if(low[u] == pre[u]) {
        int v; ++cc;
        do {
            v = S.top(); S.pop();
            comp[v] = cc, chk[v] = false;
        } while(v != u);
    }
}

int main() {
    scanf("%d %d", &n, &k);
    for(int i = 1; i <= n; i++) {
        scanf(" %s", s[i] + 1);
        for(int j = 1; j <= k; j++) if(s[i][j] == '1') {
            g[i].emplace_back(n + j);
            ++in1[n + j];
        }
    }
    for(int i = 1; i <= n; i++) for(int j = 1; j <= k; j++) if(s[i][j] == '0' && in1[n + j]) {
        g[n + j].emplace_back(i);
        ++in1[i];
    }
    for(int i = 1; i <= n + k; i++) if(!pre[i]) tarjan(i);
    for(int i = 1; i <= n + k; i++) for(int v : g[i])
        if(comp[i] != comp[v]) ++in2[comp[v]];
    int src = -1;
    for(int i = 1; i <= n; i++) if(!in2[comp[i]]) {
        if(src == -1) src = comp[i];
        else if(comp[i] != src) return !printf("-1\n");
    }
    for(int i = 1; i <= n; i++) if(comp[i] == src) printf("%d ", i);
    printf("\n");

    return 0;
}