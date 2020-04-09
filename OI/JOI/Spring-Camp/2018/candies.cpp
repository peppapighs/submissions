#include <bits/stdc++.h>

#define long long long
#define pii pair<long, long>
#define x first
#define y second

using namespace std;

const int N = 2e5+5;

int n, L[N], R[N];
long A[N];
set<pii> S;

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        scanf("%lld", A + i);
        if(i > 1) L[i] = i - 1;
        if(i < n) R[i] = i + 1;
        S.emplace(A[i], i);
    }
    long ans = 0;
    for(int i = 1; i <= (n + 1) / 2; i++) {
        int now = S.rbegin()->y;
        printf("%lld\n", ans += A[now]);
        S.erase(pii(A[now], now));
        int l = L[now], r = R[now];
        if(l) S.erase(pii(A[l], l));
        if(r) S.erase(pii(A[r], r));
        A[now] = A[l] + A[r] - A[now];
        if(l && r) {
            L[now] = L[l], R[now] = R[r];
            S.emplace(A[now], now);
        } else now = 0;
        if(L[l]) R[L[l]] = now;
        if(R[r]) L[R[r]] = now;
    }

    return 0;
}