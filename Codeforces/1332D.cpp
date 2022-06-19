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

int k;
int ans[4][4];

int main() {
    scanf("%d", &k);
    int now = 1, all = (1 << 18) - 1;
    while (now <= k)
        now *= 2;
    ans[1][1] = ans[2][2] = ans[2][3] = ans[3][2] = all;
    ans[1][2] = ans[3][3] = k, ans[2][1] = now;

    printf("3 3\n");
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++)
            printf("%d ", ans[i][j]);
        printf("\n");
    }

    return 0;
}