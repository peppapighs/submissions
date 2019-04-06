#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 1e5+5;

int n, q;
long qs[N];
vector<long> A, X;

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        long a;
        scanf("%lld", &a);
        A.emplace_back(a);
    }
    sort(A.begin(), A.end());
    A.resize(unique(A.begin(), A.end()) - A.begin());
    for(int i = 0; i < (int)A.size()-1; i++) X.emplace_back(A[i+1] - A[i]);
    sort(X.begin(), X.end());
    for(int i = 1; i <= X.size(); i++) qs[i] = qs[i-1] + X[i-1];
    scanf("%d", &q);
    for(int i = 1; i <= q; i++) {
        long a, b;
        scanf("%lld %lld", &a, &b);
        int idx = upper_bound(X.begin(), X.end(), b - a + 1) - X.begin();
        printf("%lld\n", 1ll * (b - a + 1) * ((long)A.size() - idx) + qs[idx]);
    }

    return 0;
}
