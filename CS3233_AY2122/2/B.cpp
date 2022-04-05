#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 2e4 + 5;

struct FenwickTree {
    long t[N];

    void update(int x, long k) {
        for(int i = x; i < N; i += i & -i)
            t[i] += k;
    }

    long query(int x, long ret = 0) {
        if(x <= 0) return 0;
        for(int i = x; i; i -= i & -i)
            ret += t[i];
        return ret;
    }
} t;

int n, q;
long A[N], X[25], ans[25];
vector<long> cd;

int f(long x) {
    return lower_bound(cd.begin(), cd.end(), x) - cd.begin() + 1;
}

void solve() {
    scanf("%d %d", &n, &q);	

    cd.emplace_back(0);
    for(int i = 1; i <= n; i++) {
        scanf("%lld", A + i);
        A[i] += A[i - 1];
        cd.emplace_back(A[i]);
    }
    sort(cd.begin(), cd.end());
    cd.resize(unique(cd.begin(), cd.end()) - cd.begin());

    for(int i = 1; i <= q; i++) scanf("%lld", X + i);
    t.update(f(0), 1);		

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= q; j++) {
            long xl = A[i] - X[j];
            int idx = f(xl + 1) - 1;
            ans[j] += t.query(idx);	
        }
        t.update(f(A[i]), 1);
    }
    for(int i = 1; i <= q; i++) {
        printf("%lld", ans[i]);
        if(i != q) printf(" ");
    }
    printf("\n");

    memset(A, 0, sizeof A);
    memset(X, 0, sizeof X);
    memset(ans, 0, sizeof ans);
    cd.clear();
    memset(t.t, 0, sizeof t.t);
}

int T;

int main() {
    scanf("%d", &T);
    while(T--) solve();

    return 0;
}
