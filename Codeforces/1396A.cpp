#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

#define long long long
#define iii tuple<int, int, int>
#define pii pair<int, int>
#define x first
#define y second

const int INF = 1e9 + 1;
const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
const long LINF = 1e18 + 1e10;
const double EPS = 1e-10;

using namespace std;
using namespace __gnu_pbds;

template <typename T>
using ordered_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

//-----------------------------------------------------TEMPLATE END
//HERE----------------------------------------------------------

const int N = 1e5 + 5;

int n;
long A[N];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld", A + i);
    if (n > 1) {
        printf("%d %d\n", 1, n - 1);
        for (int i = 1; i < n; i++) {
            long now = 1ll * (n - 1 + A[i]) * n - A[i];
            printf("%lld ", now);
            A[i] += now;
        }
        printf("\n");
        printf("%d %d\n%lld\n", n, n, -A[n]), A[n] = 0;
        printf("%d %d\n", 1, n);
        for (int i = 1; i <= n; i++)
            printf("%lld ", -A[i]);
        printf("\n");
    } else
        printf("1 1\n0\n1 1\n0\n1 1\n%lld\n", -A[1]);

    return 0;
}
