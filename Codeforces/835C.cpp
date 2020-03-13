#include <bits/stdc++.h>

using namespace std;

const int N = 1e5+5;

int n, q, c;
int A[105][105][15];

int main() {
    scanf("%d %d %d", &n, &q, &c);
    for(int i = 1, a, b, s; i <= n; i++) {
        scanf("%d %d %d", &a, &b, &s);
        for(int j = 0; j <= c; j++) A[a][b][j] += (s + j) % (c + 1);
    }
    for(int k = 0; k <= c; k++)
        for(int i = 1; i < 105; i++) 
            for(int j = 1; j < 105; j++) 
                A[i][j][k] += A[i-1][j][k] + A[i][j-1][k] - A[i-1][j-1][k];
    for(int i = 1, t, x1, y1, x2, y2; i <= q; i++) {
        scanf("%d %d %d %d %d", &t, &x1, &y1, &x2, &y2);
        int k = t % (c + 1);
        int ans = A[x2][y2][k] - A[x1-1][y2][k] - A[x2][y1-1][k] + A[x1-1][y1-1][k];
        printf("%d\n", ans);
    }

    return 0;
}