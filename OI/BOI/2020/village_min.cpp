#include <bits/stdc++.h>
 
using namespace std;
 
const int N = 1e5 + 5;
 
int n, deg[N], pos[N];
vector<int> g[N], cc[N];
 
int main() {
    scanf("%d", &n);
    for(int i = 1, a, b; i < n; i++) {
        scanf("%d %d", &a, &b);
        g[a].emplace_back(b);
        g[b].emplace_back(a);
        ++deg[a], ++deg[b];
    }
    queue<int> Q;
    for(int i = 1; i <= n; i++) if(deg[i] == 1)
        Q.emplace(i);
 
    int cnt = n;
    while(cnt > 2) {
        int u = Q.front(); Q.pop();
        --cnt;
        for(int v : g[u]) if(deg[v] != 1) {
            if(cc[u].empty()) cc[v].emplace_back(u);
            if(--deg[v] == 1) Q.emplace(v);
            break;
        }
    }
    if(Q.size() == 1) {
        int a = Q.front();
        if(cc[a].empty()) {
            for(int v : g[a]) if(!cc[v].empty()) {
                cc[v].emplace_back(a);
                break;
            }
        }
    }
    if(Q.size() == 2) {
        int a = Q.front(); Q.pop();
        int b = Q.front();
        if(cc[a].empty() || cc[b].empty()) {
            if(cc[a].size() > cc[b].size()) swap(a, b);
            cc[b].emplace_back(a);
        }
    }
    int ans = 0;
    for(int i = 1; i <= n; i++) if(cc[i].size()) {
        pos[i] = cc[i][0];
        for(int j = 0; j < cc[i].size() - 1; j++)
            pos[cc[i][j]] = cc[i][j + 1];
        pos[cc[i].back()] = i;
        ans += 2 * cc[i].size();
    } 
    printf("%d\n", ans);
    for(int i = 1; i <= n; i++) printf("%d ", pos[i]);
 
    return 0;
}