#include <bits/stdc++.h>

#define long long long

using namespace std;

const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};

char sub[100];
int n, m, q;
long a[40][40], sum;
bool vis[40][40];
vector<long> v;

void dfs(int x, int y) {
    if(x == n && y == m) {
        v.emplace_back(sum);
        return;
    }
    for(int i = 0; i < 4; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        if(nx < 1 || nx > n || ny < 1 || ny > m || vis[nx][ny]) continue;
        vis[nx][ny] = true, sum += a[nx][ny];
        dfs(nx, ny);
        vis[nx][ny] = false, sum -= a[nx][ny];
    }
}

int main() {
    scanf("%s", sub);
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) scanf("%lld", &a[i][j]);

    sum = a[1][1], vis[1][1] = true;
    dfs(1, 1);
    sort(v.begin(), v.end());
    scanf("%d", &q);
    for(int i = 1; i <= q; i++) {
        long a, b;
        scanf("%lld %lld", &a, &b);
        printf("%d\n", upper_bound(v.begin(), v.end(), b) - lower_bound(v.begin(), v.end(), a));
    }

    return 0;
}