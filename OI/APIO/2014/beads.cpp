#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 2e5+5;

/*
0 - Parent edge any color, No node with 2 blue edges directed to its children
1 - Parent edge must be blue, No node with 2 blue edges directed to its children
2 - Parent edge any color, 1 node in subtree with 2 blue edges directed to its children
3 - Parent edge must be blue, 1 node in subtree with 2 blue edges directed to its children
*/

int n, dp[N][4];
vector<pii> g[N];

void dfs(int u, int p) {
    for(pii v : g[u]) if(v.x != p) dfs(v.x, u);
    vector<int> V, W, M;
    vector<pii> D1, D2;
    for(pii v : g[u]) if(v.x != p) {
        V.emplace_back(v.x), W.emplace_back(v.y);
        M.emplace_back(max(dp[v.x][0], dp[v.x][1] + v.y));
        D1.emplace_back(dp[v.x][0] + v.y - M.back(), v.x);
        D2.emplace_back(dp[v.x][2] + v.y - M.back(), v.x);
    }
    sort(D1.begin(), D1.end(), greater<pii>());
    sort(D2.begin(), D2.end(), greater<pii>());

    dp[u][1] = dp[u][2] = dp[u][3] = -1e9;

    //Base Case
    for(int i = 0; i < M.size(); i++) dp[u][0] += M[i];
    //Directed one blue edge to 0-child, the other to 1-child
    for(int i = 0; i < min(2, (int)D1.size()); i++) 
        for(int j = 0; j < min(2, (int)D2.size()); j++)
            if(D1[i].y != D2[j].y) dp[u][2] = max(dp[u][2], dp[u][0] + D1[i].x + D2[j].x);
    
    //Directed 2 blue edges to 2 0-child
    if(D1.size() > 1) dp[u][2] = max(dp[u][2], dp[u][0] + D1[0].x + D1[1].x);

    //Directed 1 blue edges to 0-child, to be paired in the future
    //Directed 1 blue edges to 2-child, to be paired in the future
    for(int i = 0; i < M.size(); i++) {
        dp[u][1] = max(dp[u][1], dp[u][0] - M[i] + dp[V[i]][0] + W[i]);
        dp[u][3] = max(dp[u][3], dp[u][0] - M[i] + dp[V[i]][2] + W[i]);
    }

    //Merge with 2-child, or pair edge with 3-child
    for(int i = 0; i < M.size(); i++) 
        dp[u][2] = max(dp[u][2], dp[u][0] - M[i] + max(dp[V[i]][2], dp[V[i]][3] + W[i])); 
}

int main() {
    scanf("%d", &n);
    for(int i = 1, a, b, c; i < n; i++) {
        scanf("%d %d %d", &a, &b, &c);
        g[a].emplace_back(b, c), g[b].emplace_back(a, c);
    }
    dfs(1, 1);
    printf("%d\n", max(dp[1][0], dp[1][2]));

    return 0;
}