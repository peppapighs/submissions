#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

#define long long long
#define pii pair<int, int>
#define x first
#define y second

using namespace std;
using namespace __gnu_pbds;

template<typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

const int N = 1505;

vector<int> coord;

int get(int x) { return lower_bound(coord.begin(), coord.end(), x) - coord.begin() + 1; }

void update(long t[], int x, long k) { 
    for(int i = x+1; i < N; i += i & -i)
        t[i] += k;
}

long query(long t[], int x, long k = 0) {
    for(int i = x+1; i; i -= i & -i) 
        k += t[i];
    return k;
}

long proc[N][N], t1[N], t2[N];

int n, k, a[N];
long dp[N][55];

int main() {
    scanf("%d %d", &n, &k);
    for(int i = 1; i <= n; i++) {
        scanf("%d", a+i);
        coord.emplace_back(a[i]);
    }
    sort(coord.begin(), coord.end());
    coord.resize(unique(coord.begin(), coord.end()) - coord.begin());
    for(int l = 1; l <= n; l++) {
        int ptr = 0;
        ordered_set<pii> S; 
        memset(t1, 0, sizeof t1);
        memset(t2, 0, sizeof t2);
        for(int i = l; i <= n; i++) {
            update(t1, get(a[i]), 1);
            update(t2, get(a[i]), a[i]);
            S.insert(pii(a[i], ++ptr));
            long med = S.find_by_order(((int)S.size() - 1) / 2)->x;
            long cntl = query(t1, get(med)-1), cntr = query(t1, coord.size()) - query(t1, get(med));
            long suml = query(t2, get(med)-1), sumr = query(t2, coord.size()) - query(t2, get(med));
            proc[l][i] = (med * cntl) - suml + sumr - (med * cntr);
        }
    }
    for(int i = 1; i <= n; i++) dp[i][0] = 1e18;
    for(int x = 1; x <= k; x++) for(int i = 1; i <= n; i++) {
        dp[i][x] = 1e18;
        for(int j = 0; j < i; j++) dp[i][x] = min(dp[i][x], dp[j][x-1] + proc[j+1][i]);
    }
    long ans = 1e18;
    for(int i = 1; i <= k; i++) ans = min(ans, dp[n][i]);
    printf("%lld\n", ans);

    return 0;
}