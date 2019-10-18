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

int T;

int main() {
    scanf("%d", &T);
    while(T--) {
        int a, b, c;
        int ans = 0;
        scanf("%d %d %d", &a, &b, &c);
        for(int i = 0; i <= a; i++) {
            int ret = 0;
            if(2 * i > b) continue;
            ret += 3 * i;
            int tmp = b - 2 * i;
            if(2 * tmp > c) ret += (c / 2) + (c & 1 ? c - 1 : c);
            else ret += (3 * tmp);
            ans = max(ans, ret);
        }
        printf("%d\n", ans);
    }

    return 0;
}