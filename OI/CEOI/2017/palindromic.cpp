#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e6 + 5;

pii add(pii a, pii b) { return pii(a.x + b.x, a.y + b.y); }
pii sub(pii a, pii b) { return pii(a.x - b.x, a.y - b.y); }
pii mul(pii a, pii b) { return pii(a.x * b.x, a.y * b.y); }

int t;
char A[N];
pii iden(23, 29), hpow[N], dp[N];

int main() {
    hpow[0] = pii(1, 1);
    for (int i = 1; i < N; i++)
        hpow[i] = mul(hpow[i - 1], iden);
    scanf("%d", &t);
    while (t--) {
        int ans = 0;
        scanf(" %s", A + 1);
        hpow[0] = pii(0, 0);
        int n = strlen(A + 1);
        for (int i = 1; i <= n; i++)
            dp[i] = add(mul(dp[i - 1], iden), pii(A[i], A[i]));
        int sz = 0;
        for (int i = 1, j = n; i <= j; i++, j--) {
            ++sz;
            int l = i - sz, r = j + sz - 1;
            pii lhs = sub(dp[i], mul(dp[l], hpow[sz]));
            pii rhs = sub(dp[r], mul(dp[j - 1], hpow[sz]));
            if (lhs == rhs && i != j)
                ans += 2, sz = 0;
            if (lhs == rhs && i == j)
                ++ans, sz = 0;
        }
        if (sz)
            ++ans;
        printf("%d\n", ans);
    }

    return 0;
}
