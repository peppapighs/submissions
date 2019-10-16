#include <bits/stdc++.h>

using namespace std;

int k, n, m, q;
int bl[50005][5][5][16];

int main() {
    fill_n(bl[0][0][0], 50005 * 5 * 5 * 16, 1e9);
    scanf("%d %d %d %d", &k, &n, &m, &q);
    for(int i = 1, a, b, c; i <= m; i++) {
        scanf("%d %d %d", &a, &b, &c);
        bl[a / k][a % k][b % k][0] = c;
    }
    for(int i = 1; i <= 15; i++) for(int a = 0; a <= n / k + 1; a++) 
        for(int b = 0; b < k; b++) for(int c = 0; c < k; c++) for(int t = 0; t < k; t++)
            if(a + (1 << (i - 1)) <= n / k + 1)
                bl[a][b][c][i] = min(bl[a][b][c][i], bl[a][b][t][i-1] + bl[a + (1 << (i - 1))][t][c][i-1]);
    while(q--) {
        int a, b;
        scanf("%d %d", &a, &b);
        if(a / k >= b / k) {
            printf("-1\n");
            continue;
        }
        int ans = b % k, dp[5];
        for(int i = 0; i < k; i++) dp[i] = bl[a / k][a % k][i][0];
        a = (a / k) + 1, b = b / k;
        for(int i = 15; ~i; i--) if(a + (1 << i) <= b) {
            int ndp[5];
            fill_n(ndp, 5, 1e9);
            for(int x = 0; x < k; x++) for(int y = 0; y < k; y++)
                ndp[x] = min(ndp[x], dp[y] + bl[a][y][x][i]);
            for(int j = 0; j < k; j++) dp[j] = ndp[j];
            a += (1 << i);
        }
        if(dp[ans] == 1e9) printf("-1\n");
        else printf("%d\n", dp[ans]);
    }

    return 0;
}