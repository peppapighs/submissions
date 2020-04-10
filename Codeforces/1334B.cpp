#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 1e5+5;

int n, x, A[N];

void solve() {
    scanf("%d %d", &n, &x);
    int cnt = 0, ans;
    for(int i = 1; i <= n; i++) {
        scanf("%d", A + i);
        if(A[i] >= x) ++cnt;
    }
    sort(A + 1, A + n + 1, greater<int>());
    ans = cnt;
    long sum = 0;
    for(int i = 1; i <= n; i++) {
        if(A[i] >= x) --cnt;
        sum += A[i];
        if(sum >= 1ll * x * i) ans = max(ans, i + cnt);
    }
    printf("%d\n", ans);
}

int T;

int main() {
    scanf("%d", &T);
    while(T--) solve();

    return 0;
}