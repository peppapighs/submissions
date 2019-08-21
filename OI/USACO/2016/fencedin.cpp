#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 5e4+5;

int A, B, n, m;
vector<int> row, col, X, Y;

int main() {
    freopen("fencedin.in", "r", stdin);
    freopen("fencedin.out", "w", stdout);

    scanf("%d %d %d %d", &A, &B, &n, &m);
    for(int i = 1, a; i <= n; i++) {
        scanf("%d", &a);
        row.emplace_back(a);
    }
    for(int i = 1, a; i <= m; i++) {
        scanf("%d", &a);
        col.emplace_back(a);
    }
    sort(row.begin(), row.end()), sort(col.begin(), col.end());

    X.emplace_back(row[0]), Y.emplace_back(col[0]);
    for(int i = 1; i < n; i++) X.emplace_back(row[i] - row[i-1]);
    for(int i = 1; i < m; i++) Y.emplace_back(col[i] - col[i-1]);
    X.emplace_back(A - row.back()), Y.emplace_back(B - col.back());

    sort(X.begin(), X.end()), sort(Y.begin(), Y.end());

    int l = 1, r = 1;
    long ans = 1ll * X[0] * m + 1ll * Y[0] * n;
    while(l <= n && r <= n) {
        if(X[l] < Y[r]) ans += 1ll * X[l++] * (m - r + 1);
        else ans += 1ll * Y[r++] * (n - l + 1);
    }
    printf("%lld\n", ans); 

    return 0;
}