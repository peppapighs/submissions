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
int A[N], B[N];
bool add[N], sub[N];

void solve() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", A + i);
        add[i] = add[i - 1] | (A[i] == 1);
        sub[i] = sub[i - 1] | (A[i] == -1);
    }
    for (int i = 1; i <= n; i++)
        scanf("%d", B + i);
    for (int i = n; i; i--) {
        if (A[i] < B[i] && !add[i - 1]) {
            printf("NO\n");
            return;
        }
        if (A[i] > B[i] && !sub[i - 1]) {
            printf("NO\n");
            return;
        }
    }
    printf("YES\n");
}

int T;

int main() {
    scanf("%d", &T);
    while (T--)
        solve();

    return 0;
}