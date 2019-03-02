#include <bits/stdc++.h>

using namespace std;

const int N = 1e5+5;

int n;
int dp[N];
vector<int> g[N];

void dfs(int u, int p) {
    priority_queue<int, vector<int>, greater<int> > Q;
    for(int v : g[u]) if(v != p) {
        dfs(v, u);
        Q.emplace(dp[v]);
    }
    if(Q.empty()) dp[u] = 0;
    else if(Q.size() == 1) dp[u] = Q.top() + 1;
    else {
        while(Q.size() > 2) {
            int a = Q.top(); Q.pop();
            int b = Q.top(); Q.pop();
            Q.emplace(b + 1);
        }
        Q.pop();
        dp[u] = Q.top() + 1;
    }
}

int main() {
    scanf("%d", &n);
    for(int i = 2, p; i <= n; i++) {
        scanf("%d", &p);
        g[i].emplace_back(p), g[p].emplace_back(i);
    }
    dfs(1, 1);
    printf("%d\n", dp[1]);

    return 0;
}