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

int n, m;
int A[105][105];

void solve() {
    memset(A, 0, sizeof A);

    scanf("%d %d", &n, &m);
    if(n == 1) {
        for(int i = 1; i <= m; i++) if(i & 1) A[1][i] = 1;
        if(m % 2 == 0) A[1][m] = 1;
    } else if(m == 1) {
        for(int i = 1; i <= n; i++) if(i & 1) A[i][1] = 1;
        if(n % 2 == 0) A[n][1] = 1;
    } else {
        for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) if((i & 1) == (j & 1))
            A[i][j] = 1;
        if(n * m % 2 == 0) A[1][2] = 1;
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(A[i][j] == 1) printf("B");
            else printf("W");
        }
        printf("\n");
    }
}

int T;

int main() {
    scanf("%d", &T);
    while(T--) solve();

    return 0;
}