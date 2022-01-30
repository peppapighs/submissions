#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 2e5 + 5;

int n;
int A[N], pos[N], ans[N];

void solve() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        scanf("%d", A + i);
        pos[i] = i;
    }
    sort(pos + 1, pos + n + 1, [&](int &a, int &b) {
        return A[a] > A[b];
    });
    long sum = 0;
    for(int i = 1; i <= n; i++) {
        ans[pos[i]] = ((i + 1) / 2) * (i % 2 == 0 ? 1 : -1);
        sum += 1ll * A[pos[i]] * ((i + 1) / 2);
    }
    printf("%lld\n0 ", sum * 2);
    for(int i = 1; i <= n; i++) printf("%d ", ans[i]);
    printf("\n");
}

int T;

int main() {
    scanf("%d", &T);
    while(T--) solve();

    return 0;
}