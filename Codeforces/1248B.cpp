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

const int N = 1e5+5;

int n;
long a[N];

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%lld", a + i);
    sort(a + 1, a + n + 1);
    long c = 0, d = 0;
    for(int i = 1; i <= n; i++) {
        if(i <= n / 2) c += a[i];
        else d += a[i];
    }
    printf("%lld\n", c * c + d * d);

    return 0;
}