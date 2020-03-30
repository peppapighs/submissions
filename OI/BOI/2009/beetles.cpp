#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 305;

int n, m, pos[N];
long L[N][N], R[N][N];

long d(int x, int y) { return abs(pos[x] - pos[y]); }

int main() {
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; i++) scanf("%d", pos + i);
    sort(pos + 1, pos + n + 1);

    long ans = 0;
    for(int len = 1; len <= n; len++) {
        for(int i = n; i; i--) for(int j = i; j <= n; j++) {
            if(j - i + 1 > len) continue;
            if(i == j) L[i][j] = R[i][j] = 1ll * len * abs(pos[i]);
            else {
                int sz = j - i + 1;
                L[i][j] = min(L[i + 1][j] + d(i, i + 1) * (len - sz + 1), R[i + 1][j] + d(i, j) * (len - sz + 1));
                R[i][j] = min(L[i][j - 1] + d(i, j) * (len - sz + 1), R[i][j - 1] + d(j - 1, j) * (len - sz + 1));
            }
        }
        for(int i = 1, j = len; j <= n; i++, j++)
            ans = max(ans, 1ll * len * m - min(L[i][j], R[i][j]));
    }
    printf("%lld\n", ans);

    return 0;
}