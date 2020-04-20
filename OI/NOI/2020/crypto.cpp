#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 3e5+5;
const int M = 1e9+7;

int n, A[N];
long fac[N];
vector<int> coord;

int get(int x) {
    return lower_bound(coord.begin(), coord.end(), x) - coord.begin() + 1;
}

int t[N];

void update(int x, int k) {
    for(int i = x; i < N; i += i & -i)
        t[i] += k;
}

int query(int x, int ret = 0) {
    for(int i = x; i; i -= i & -i)
        ret += t[i];
    return ret;
}

int main() {
    fac[0] = 1;
    for(int i = 1; i < N; i++) fac[i] = fac[i-1] * i % M;

    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        scanf("%d", A + i);
        coord.emplace_back(A[i]);
    }
    sort(coord.begin(), coord.end());
    
    long ans = 0;
    for(int i = 1; i <= n; i++) {
        int idx = query(get(A[i]));
        ans = (ans + fac[n - i] * (get(A[i]) - idx - 1) % M) % M;
        update(get(A[i]), 1);
    }
    printf("%lld\n", (ans + 1) % M);

    return 0;
}