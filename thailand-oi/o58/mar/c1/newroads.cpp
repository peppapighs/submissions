#include <bits/stdc++.h>

#define long long long
#define iii tuple<int, int, int>

using namespace std;

const int N = 1e5+5;

int n, m, weight[N<<1], cnt;
int chk[N<<1], rev[N<<1];
long sum, ret;
vector<iii> g[N];

void euler(int u) {
    int v, idx, r;
    while(!g[u].empty() && chk[get<1>(g[u].back())]) g[u].pop_back();
    if(g[u].empty()) return;
    iii now = g[u].back(); g[u].pop_back();
    tie(v, idx, r) = now;
    chk[idx] = 1, rev[idx] = r;
    euler(v);
}

int main() {
    scanf("%d %d", &n, &m);
    for(int i = 1, a, b; i <= m; i++) {
        scanf("%d %d %d", &a, &b, weight+i);
        g[a].emplace_back(b, i, 0);
        g[b].emplace_back(a, i, 1);
        sum += weight[i];
    }
    for(int i = 1; i <= n; i++) if(g[i].size()) euler(i);
    for(int i = 1; i <= m; i++) if(rev[i]) ++cnt, ret += weight[i];
    bool valid = (ret << 1) > sum ? 1 : 0;
    printf("%d\n", valid ? m - cnt : cnt);
    for(int i = 1; i <= m; i++) if(rev[i] ^ valid) printf("%d\n", i);

    return 0; 
}