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

const int N = 2e5+5;

int n, A[N];
long qs[N], ans;
map<long, int> mp;

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%d", A + i), qs[i] = qs[i-1] + A[i];
    mp[0] = 0;
    int mx = -1;
    for(int i = 1; i <= n; i++) {
        if(!mp.count(qs[i])) {
            if(mx == -1) ans += i;
            else ans += i - mx;
        } else {
            ans += min(i - mp[qs[i]] - 1, i - mx);
            mx = max(mx, mp[qs[i]] + 1);
        }
        mp[qs[i]] = i;
    }
    printf("%lld\n", ans);

    return 0;
}