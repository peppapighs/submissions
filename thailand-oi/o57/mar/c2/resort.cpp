#include <bits/stdc++.h>

using namespace std;

const int N = 1e3+5;

int n, m, t, ans = 1e9;
int A[N][N];

int main() {
    scanf("%d %d %d", &n, &m, &t);
    for(int i = 1, a, b; i <= n; i++) {
        scanf("%d %d", &a, &b);
        ++A[++a][++b];
    }
    for(int i = 1; i <= m; i++) for(int j = 1; j <= m; j++)
       A[i][j] += A[i-1][j] + A[i][j-1] - A[i-1][j-1];
    for(int i = 1; i <= m; i++) for(int j = i; j <= m; j++) {
        int l = 1, r = m;
        while(l < r) {
            int mid = (l + r) >> 1;
            if(A[mid][j] - A[mid][i-1] >= t) r = mid;
            else l = mid + 1;
        }
        if(A[r][j] - A[r][i-1] >= t) ans = min(ans, (j - i + 1) * r);
    }
    printf("%d\n", ans);

    return 0;
}
