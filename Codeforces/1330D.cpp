#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

#define long long long
#define iii tuple<int, int, int>
#define pii pair<int, int>
#define x first
#define y second

const int INF = 1e9+1;
const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
const long LINF = 1e18 + 1e10;
const double EPS = 1e-10;

using namespace std;
using namespace __gnu_pbds;

template<typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

//-----------------------------------------------------TEMPLATE END HERE----------------------------------------------------------

long modpow(long a, long b, long M) {
    long ret = 1;
    for( ; b; b >>= 1) {
        if(b & 1) ret = ret * a % M;
        a = a * a % M;
    }
    return ret;
}

int d, M;

void solve() {
    scanf("%d %d", &d, &M);
    if(d == 1) {
        printf("%d\n", 1 % M);
        return;
    }
    int now = 1;
    long ans = 1, dif = 2;
    for(int i = 1; i <= 30; i++) {
        if(now + (1 << i) >= d) break;
        ans += dif * (1 << i) % M; 
        ans %= M;
        now += (1 << i);
        dif *= (((1 << i) + 1) % M);
        dif %= M;
    }
    ans += dif * (d - now) % M;
    ans %= M;
    printf("%lld\n", ans);
}

int T;

int main() {
    scanf("%d", &T);
    while(T--) solve();

    return 0;
}