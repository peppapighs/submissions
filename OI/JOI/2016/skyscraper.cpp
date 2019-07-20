#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 105;
const int L = 1e3+5;
const int M = 1e9+7;

int n, l, a[N];
long dp[N][N][L][3];

long solve(int pos, int cc, int diff, int ends) {
    if(pos == n + 1) return (cc == 1 && diff <= l && ends == 2);
    if(cc == 0 || diff > l || ends == 3) return 0;
    long &now = dp[pos][cc][diff][ends];
    if(~now) return now;
    
    int ndiff = diff + (a[pos] - a[pos - 1]) * (2 * cc - ends);

    now = 0;
    now = (now + (cc + 1 - ends) * solve(pos + 1, cc + 1, ndiff, ends) % M) % M;
    now = (now + (2 * cc - ends) * solve(pos + 1, cc, ndiff, ends) % M) % M;
    now = (now + (cc - 1) * solve(pos + 1, cc - 1, ndiff, ends) % M) % M;
    now = (now + (2 - ends) * solve(pos + 1, cc + 1, ndiff, ends + 1) % M) % M;
    now = (now + (2 - ends) * solve(pos + 1, cc, ndiff, ends + 1) % M) % M;

    return now;
}

int main() {
    memset(dp, -1, sizeof dp);

    scanf("%d %d", &n, &l);
    for(int i = 1; i <= n; i++) scanf("%d", a + i);
    sort(a + 1, a + n + 1);

    if(n == 1) return !printf("1\n");
    printf("%lld\n", (solve(2, 1, 0, 0) + 2 * solve(2, 1, 0, 1)) % M);

    return 0;
}