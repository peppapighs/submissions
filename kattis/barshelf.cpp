#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 2e5 + 5;

struct FenwickTree {
    long t[N];
    
    void update(int x, int k) {
        for(int i = x; i < N; i += i & -i)
            t[i] += k;
    }

    long query(int x, long ret = 0) {
        if(x == 0) return 0;
        for(int i = x; i; i -= i & -i)
            ret += t[i];
        return ret; 
    }
} t_l, t_r;

int n;
int A[N];
vector<int> coord;

int f(int x) { return lower_bound(coord.begin(), coord.end(), x) - coord.begin() + 1; }

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        scanf("%d", A + i);
        coord.emplace_back(A[i]);
    }
    sort(coord.begin(), coord.end());
    coord.resize(unique(coord.begin(), coord.end()) - coord.begin());

    for(int i = 1; i <= n; i++) t_r.update(f(A[i]), 1);
    long ans = 0;
    for(int i = 1; i <= n; i++) {
        t_r.update(f(A[i]), -1);
        int doub = f(A[i] * 2), half = f(A[i] / 2 + 1) - 1;
        ans += (t_l.query(N - 1) - t_l.query(doub - 1)) * t_r.query(half);
        t_l.update(f(A[i]), 1);
    }
    printf("%lld\n", ans);

    return 0;
}