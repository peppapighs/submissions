#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 2e5+5;

int n, A[N], col[N], in[N];
int dp[N][4], pref[N], ans;
vector<int> g[N], C;

void findcyc(int u, int p) {
    static vector<int> S;
    col[u] = 1;
    S.emplace_back(u);
    for(int v : g[u]) if(v != p) {
        if(!col[v]) findcyc(v, u);
        else if(col[v] == 1) while(C.empty() || C.back() != v) {
            in[S.back()] = 1;
            C.emplace_back(S.back());
            S.pop_back();
        }
    }
    col[u] = 2;
}

void dfs(int u, int p) {
    dp[u][0] = A[u];
    vector<int> V = {0, 0, 0};
    for(int v : g[u]) if(v != p && !in[v]) {
        dfs(v, u);
        V.emplace_back(dp[v][2]);
    }
    sort(V.begin(), V.end(), greater<int>());
    for(int i = 1; i <= 3; i++) dp[u][i] = dp[u][i-1] + V[i-1];
}

int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; i++) scanf("%d", A+i);
    for(int i = 1, a, b; i <= n; i++) {
        scanf("%d %d", &a, &b);
        g[a].emplace_back(b), g[b].emplace_back(a);
    }
    findcyc(0, 0);
    int sum = 0;
    for(int u : C) dfs(u, u), ans = max(ans, dp[u][3]), sum += dp[u][1];
    ans = max(ans, sum);
    deque<pii> Q;
    pref[0] = dp[C[0]][1];
    for(int i = 1; i < C.size(); i++) pref[i] = pref[i-1] + dp[C[i]][1];
    for(int i = 1; i < C.size(); i++) {
        int now = dp[C[i]][2] + pref[i-1] - pref[0];
        while(!Q.empty() && Q.back().x < now) Q.pop_back();
        Q.emplace_back(now, i);
    }
    ans = max(ans, Q.front().x + dp[C[0]][2]);
    for(int i = 0; i < C.size()-1; i++) {
        if(Q.front().y == i+1) Q.pop_front();
        int now = dp[C[i]][2] + pref[C.size()-1] + pref[i-1] - pref[0];
        while(!Q.empty() && Q.back().x < now) Q.pop_back();
        Q.emplace_back(now, i);
        ans = max(ans, Q.front().x - pref[i+1] + pref[0] + dp[C[i+1]][2]);
    }
    printf("%d\n", ans);

    return 0;
}