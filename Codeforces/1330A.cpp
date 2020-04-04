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

int n, x;
int A[205];

void solve() {
    memset(A, 0, sizeof A);

    scanf("%d %d", &n, &x);
    for(int i = 1, a; i <= n; i++) {
        scanf("%d", &a);
        A[a] = 1;
    }
    int ans = 0;
    for(int i = 1; ; i++) {
        if(!A[i]) {
            if(x) --x;
            else break;
        }
        ++ans;
    }
    printf("%d\n", ans);
}

int T;

int main() {
    scanf("%d", &T);
    while(T--) solve();

    return 0;
}