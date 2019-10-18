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

int count(int a, int b, vector<int> &v) {
    return upper_bound(v.begin(), v.end(), b) - lower_bound(v.begin(), v.end(), a);
}

int n, m, k;
vector<int> R, C;
map<int, vector<int> > row, col;

int main() {
    scanf("%d %d %d", &n, &m, &k);
    for(int i = 1, a, b; i <= k; i++) {
        scanf("%d %d", &a, &b);
        row[a].emplace_back(b);
        col[b].emplace_back(a);
    }
    for(auto &p : row) sort(p.y.begin(), p.y.end());
    for(auto &p : col) sort(p.y.begin(), p.y.end());
    int r1 = 1, r2 = n, c1 = 1, c2 = m;
    long sum = 0;
    for(int t = 0; r1 <= r2 && c1 <= c2; t++) {
        if(t % 4 == 0) {
            while(count(r1, r2, col[c2]) == r2 - r1 + 1) --c2;
            if(count(c1, c2, row[r1]) != 0) return !printf("No\n");
            ++r1;
        } else if(t % 4 == 1) {
            while(count(c1, c2, row[r2]) == c2 - c1 + 1) --r2;
            if(count(r1, r2, col[c2]) != 0) return !printf("No\n");
            --c2;
        } else if(t % 4 == 2) {
            while(count(r1, r2, col[c1]) == r2 - r1 + 1) ++c1;
            if(count(c1, c2, row[r2]) != 0) return !printf("No\n");
            --r2;
        } else {
            while(count(c1, c2, row[r1]) == c2 - c1 + 1) ++r1;
            if(count(r1, r2, col[c1]) != 0) return !printf("No\n");
            ++c1;
        }
    }
    printf("Yes\n");

    return 0;
}