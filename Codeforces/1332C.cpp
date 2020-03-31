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

int n, k;
int cnt[N][26];
char A[N];

void solve() {
    scanf("%d %d %s", &n, &k, A + 1);
    int rep = n / k;
    for(int i = 1; i <= k; i++) for(int j = i; j <= n; j += k) ++cnt[i][A[j] - 'a'];

    int ans = 0;
    for(int i = 1; i <= k / 2; i++) {
        int mn = 1e9;
        for(int j = 0; j < 26; j++) mn = min(mn, 2 * rep - cnt[i][j] - cnt[k - i + 1][j]);
        ans += mn;
    }
    if(k & 1) {
        int mn = 1e9;
        for(int j = 0; j < 26; j++) mn = min(mn, rep - cnt[(k + 1) / 2][j]);
        ans += mn;
    }
    printf("%d\n", ans);

    for(int i = 1; i <= k; i++) for(int j = 0; j < 26; j++) cnt[i][j] = 0;
}

int t;

int main() {
    scanf("%d", &t);
    while(t--) solve();

    return 0;
}