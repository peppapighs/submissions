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

const int N = 1e3+5;

int p[11] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31 };

int n;
int A[N], chk[N], ans[N];
vector<int> idx[11];

void solve() {
    scanf("%d", &n);
    memset(chk, 0, sizeof chk);
    for(int j = 0; j < 11; j++) idx[j].clear();
    for(int i = 1; i <= n; i++) {
        scanf("%d", A + i);
        for(int j = 0; j < 11; j++) 
            if(A[i] % p[j] == 0) idx[j].emplace_back(i);
    }
    int cnt = 0;
    for(int i = 10; ~i; i--) {
        int now = 0;
        for(int x : idx[i]) if(!chk[x])
            ++now;
        if(now) {
            ++cnt;
            for(int x : idx[i]) if(!chk[x]) {
                ans[x] = cnt;
                chk[x] = true;
            }
        }
    }
    printf("%d\n", cnt);
    for(int i = 1; i <= n; i++) printf("%d ", ans[i]);
    printf("\n");
}

int t;

int main() {
    scanf("%d", &t);
    while(t--) solve();

    return 0;
}