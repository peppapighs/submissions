#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 1255;

void update(long t[], int x, long k) { 
    x += N;
    for(t[x] = min(t[x], k); x != 1; x >>= 1) 
        t[x>>1] = min(t[x], t[x^1]); 
}

long query(long t[], int l, int r) {
    long ret = 1e12;
    for(l += N, r += N+1; l < r; l >>= 1, r >>= 1) {
        if(l & 1) ret = min(ret, t[l++]);
        if(r & 1) ret = min(ret, t[--r]);
    }
    return ret;
}

int get(vector<int> &V, int x) { return lower_bound(V.begin(), V.end(), x) - V.begin(); }

int R, C, A[N][N];
long row[N][N], col[N][N];
long dp[N][N], tr[N][N<<1], tc[N][N<<1];
vector<int> r[N], c[N];

int main() {
    fill_n(dp[0], N*N, 1e12), fill_n(tr[0], N*(N<<1), 1e12), fill_n(tc[0], N*(N<<1), 1e12);

    scanf("%d %d", &R, &C);
    for(int i = 1; i <= R; i++) for(int j = 1; j <= C; j++) {
        scanf("%d", &A[i][j]);
        col[i][j] = row[i][j] = A[i][j];
        r[i].emplace_back(A[i][j]);
        c[j].emplace_back(A[i][j]);
    }

    for(int i = 1; i <= R; i++) for(int j = 1; j <= C; j++)
        row[i][j] += row[i][j-1], col[i][j] += col[i-1][j];

    for(int i = 1; i <= R; i++) {
        sort(r[i].begin(), r[i].end());
        r[i].resize(unique(r[i].begin(), r[i].end()) - r[i].begin());
    }
    for(int i = 1; i <= C; i++) {
        sort(c[i].begin(), c[i].end());
        c[i].resize(unique(c[i].begin(), c[i].end()) - c[i].begin());
    }

    for(int i = 1; i <= R; i++) for(int j = 1; j <= C; j++) {
        int idR = get(r[i], A[i][j]), idC = get(c[j], A[i][j]);

        if(i == 1 && j == 1) dp[i][j] = 0;
        else dp[i][j] = min(row[i][j-1] + query(tr[i], 0, idR-1), col[i-1][j] + query(tc[j], 0, idC-1));
        update(tr[i], idR, dp[i][j] - row[i][j]), update(tc[j], idC, dp[i][j] - col[i][j]); 
    }
    if(dp[R][C] == 1e12) printf("-1\n");
    else printf("%lld\n", dp[R][C]);

    return 0;
}
