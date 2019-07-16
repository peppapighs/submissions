#include <bits/stdc++.h>

using namespace std;

const int N = 505;
const int M = 5e3+5;

int r, c, m;
char a[N][N], dir[M];
bitset<N> mask[N], dp[N];

int main() {
    scanf("%d %d %d", &r, &c, &m);
    for(int i = 0; i < r; i++) {
        scanf(" %s", a[i]);
        for(int j = 0; j < c; j++) {
            if(a[i][j] == '#') mask[i][j] = dp[i][j] = 0;
            else mask[i][j] = dp[i][j] = 1;
        }
    }
    scanf(" %s", dir);
    for(int i = 0; i < m; i++) {
        bitset<N> ndp[N];
        for(int j = 0; j < r; j++) ndp[j] = 0;
        if(dir[i] == 'N' || dir[i] == '?') for(int j = 0; j < r - 1; j++)
            ndp[j] |= dp[j + 1];
        if(dir[i] == 'S' || dir[i] == '?') for(int j = 1; j < r; j++)
            ndp[j] |= dp[j - 1];
        if(dir[i] == 'W' || dir[i] == '?') for(int j = 0; j < r; j++)
            ndp[j] |= dp[j] >> 1;
        if(dir[i] == 'E' || dir[i] == '?') for(int j = 0; j < r; j++)
            ndp[j] |= dp[j] << 1;
        for(int j = 0; j < r; j++) dp[j] = ndp[j] & mask[j];
    }
    int ans = 0;
    for(int i = 0; i < r; i++) ans += dp[i].count();
    printf("%d\n", ans);

    return 0;
}