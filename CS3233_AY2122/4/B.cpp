#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 51;
const long INF = 1e18;

int T;
int n, v, e;
long A[N][N], ans[N][N], tmp[N][N];

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d %d", &n, &v, &e);
        for (int i = 0; i < v; i++)
            for (int j = 0; j < v; j++)
                A[i][j] = ans[i][j] = -INF;
        for (int i = 0, a, b, c; i < e; i++) {
            scanf("%d %d %d", &a, &b, &c);
            A[a][b] = c;
            ans[a][b] = c;
        }
        n -= 2;
        for (; n; n >>= 1) {
            if (n & 1) {
                fill_n(tmp[0], N * N, -INF);
                for (int k = 0; k < v; k++)
                    for (int i = 0; i < v; i++)
                        for (int j = 0; j < v; j++) {
                            if (ans[i][k] == -INF || A[k][j] == -INF)
                                continue;
                            tmp[i][j] = max(tmp[i][j], ans[i][k] + A[k][j]);
                        }
                for (int i = 0; i < v; i++)
                    for (int j = 0; j < v; j++)
                        ans[i][j] = tmp[i][j];
            }
            fill_n(tmp[0], N * N, -INF);
            for (int k = 0; k < v; k++)
                for (int i = 0; i < v; i++)
                    for (int j = 0; j < v; j++) {
                        if (A[i][k] == -INF || A[k][j] == -INF)
                            continue;
                        tmp[i][j] = max(tmp[i][j], A[i][k] + A[k][j]);
                    }
            for (int i = 0; i < v; i++)
                for (int j = 0; j < v; j++)
                    A[i][j] = tmp[i][j];
        }
        long ret = -INF;
        for (int i = 0; i < v; i++) {
            for (int j = 0; j < v; j++) {
                ret = max(ret, ans[i][j]);
            }
        }
        if (ret == -INF)
            printf("Sad bunny :(\n");
        else
            printf("%lld\n", ret);
    }

    return 0;
}
