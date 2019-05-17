#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 1e5+5;

int n, m, b[N], g[N];
long ans, sumb, sumg;

int main() {
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; i++) scanf("%d", b+i), sumb += b[i];
    for(int i = 1; i <= m; i++) scanf("%d", g+i), sumg += g[i];
    sort(b+1, b+n+1), sort(g+1, g+m+1);
    if(g[1] < b[n]) return !printf("-1\n");
    if(g[1] == b[n]) printf("%lld\n", sumg + (sumb - b[n]) * m);
    else {
        ans = (sumg - g[m]) + b[n];
        bool valid = false;
        for(int i = n-1; i; i--) {
            if(!valid && g[m] >= b[i]) {
                ans += 1ll * b[i] * (m-1) + g[m];
                valid = true;
            } else ans += 1ll * b[i] * m;
        }
        if(!valid) printf("-1\n");
        else printf("%lld\n", ans);
    }

    return 0;
}