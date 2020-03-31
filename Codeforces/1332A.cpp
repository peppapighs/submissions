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

int a, b, c, d;
int x, y, x1, Y1, x2, y2;

void solve() {
    scanf("%d %d %d %d", &a, &b, &c, &d);
    scanf("%d %d %d %d %d %d", &x, &y, &x1, &Y1, &x2, &y2);
    if(x1 == x2 && (a || b)) {
        printf("No\n");
        return;
    }
    if(Y1 == y2 && (c || d)) {
        printf("No\n");
        return;
    }
    int nx = x + b - a, ny = y + d - c; 
    if(x1 <= nx && nx <= x2 && Y1 <= ny && ny <= y2)
        printf("Yes\n");
    else printf("No\n");
}

int t;

int main() {
    scanf("%d", &t);
    while(t--) solve();

    return 0;
}