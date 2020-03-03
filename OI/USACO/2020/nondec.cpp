#include <bits/stdc++.h>

#define long long long
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 2e5+5;
const int M = 1e9+7;

long add(long a, long b) { return a + b > M ? a + b - M : a + b; }

int n, k, q, A[N];
long dp1[N][25], dp2[N][25], sum[25], ans[N];
vector<pii> Q[N];

void find_l(int l, int r) {
    for(int i = l-1; i <= r; i++) for(int j = 0; j <= k; j++)
        dp1[i][j] = 0;
    for(int x = k; x; x--) {
        for(int i = x; i <= k; i++) sum[i] = 0;
        for(int i = r; i >= l; i--) {
            if(A[i] == x) {
                sum[x] = add(sum[x], sum[x] + 1);
                for(int j = x + 1; j <= k; j++) sum[j] = add(sum[j], add(sum[j], dp1[i][j]));
            }
            for(int j = x; j <= k; j++) dp1[i][j] = add(dp1[i][j], sum[j]);
        } 
    }
}

void find_r(int l, int r) {
    for(int i = l; i <= r+1; i++) for(int j = 1; j <= k+1; j++)
        dp2[i][j] = 0;
    for(int x = 1; x <= k; x++) {
        for(int i = 1; i <= x; i++) sum[i] = 0;
        for(int i = l; i <= r; i++) {
            if(A[i] == x) {
                sum[x] = add(sum[x], sum[x] + 1);
                for(int j = 1; j < x; j++) sum[j] = add(sum[j], add(sum[j], dp2[i][j])); 
            }
            for(int j = 1; j <= x; j++) dp2[i][j] = add(dp2[i][j], sum[j]);
        }
    }
}

void solve(int l, int r) {
    if(l == r) {
        for(pii q : Q[l]) if(q.x == r)
            ans[q.y] = 1;
        return;
    }
    int mid = (l + r) >> 1;
    find_l(l, mid), find_r(mid + 1, r);

    for(int i = mid + 1; i <= r; i++) for(int j = k; j; j--)
        dp2[i][j] = add(dp2[i][j], dp2[i][j+1]);

    for(int i = l; i <= mid; i++) for(pii q : Q[i]) {
        if(q.x <= mid || q.x > r) continue;
        int L = i, R = q.x;
        for(int j = 1; j <= k; j++) {
            ans[q.y] = add(ans[q.y], dp1[L][j] * dp2[R][j] % M);
            ans[q.y] = add(ans[q.y], dp1[L][j]);
        }
        ans[q.y] = add(ans[q.y], dp2[R][1]); 
    }

    solve(l, mid), solve(mid + 1, r);
}

int main() {
    freopen("nondec.in", "r", stdin);
    freopen("nondec.out", "w", stdout);

    scanf("%d %d", &n, &k);
    for(int i = 1; i <= n; i++) scanf("%d", A + i);
    scanf("%d", &q);
    for(int i = 1, l, r; i <= q; i++) {
        scanf("%d %d", &l, &r);
        Q[l].emplace_back(r, i);
    }

    solve(1, n);
    for(int i = 1; i <= q; i++) printf("%lld\n", ans[i] + 1);

    return 0;
}