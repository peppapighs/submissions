#include <bits/stdc++.h>

using namespace std;

const int N = 505;

int n, m;
int a[N][N], b[N][N];

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &a[i][j]);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &b[i][j]);
    for (int i = 1; i < n; i++)
        for (int j = 1; j < m; j++)
            if (a[i][j] != b[i][j]) {
                a[i][j] ^= 1;
                a[i][j + 1] ^= 1;
                a[i + 1][j] ^= 1;
                a[i + 1][j + 1] ^= 1;
            }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (a[i][j] != b[i][j])
                return !printf("No\n");
    printf("Yes\n");

    return 0;
}
