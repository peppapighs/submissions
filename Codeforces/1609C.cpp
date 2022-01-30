#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 1e6 + 5;

int n, e;
int sieve[N], prime[N];

void solve() {
    scanf("%d %d", &n, &e);
    vector<vector<int>> mod(e, vector<int>());
    for(int i = 1, a; i <= n; i++) {
        scanf("%d", &a);
        mod[i % e].emplace_back(a);
    }

    long ans = 0;
    for(int m = 0; m < e; m++) {
        vector<int> &vec = mod[m];
        vector<int> l(vec.size()), r(vec.size());
        for(int i = 0, lp = 0; i < vec.size(); i++) {
            if(prime[vec[i]]) l[i] = lp;
            if(vec[i] != 1) lp = i + 1;
        }
        for(int i = vec.size() - 1, rp = vec.size() - 1; i >= 0; i--) {
            if(prime[vec[i]]) r[i] = rp;
            if(vec[i] != 1) rp = i - 1;
        }
        for(int i = 0; i < vec.size(); i++) if(prime[vec[i]])
            ans += 1ll * (i - l[i] + 1) * (r[i] - i + 1) - 1;
    }
    printf("%lld\n", ans);
}

int T;

int main() {
    for(int i = 2; i < N; i++) if(!sieve[i]) {
        prime[i] = 1;
        for(int j = i; j < N; j += i)
            sieve[j] = 1;
    }

    scanf("%d", &T);
    while(T--) solve();

    return 0;
}