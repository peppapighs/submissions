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
 
const int N = 105;
 
int n, A[N];
 
void solve() {
    scanf("%d", &n);
    int mx = -1, sum = 0;
    for(int i = 1; i <= n; i++) {
        scanf("%d", A + i);
        mx = max(mx, A[i]), sum += A[i];
    }
    if(n == 2) {
        if(A[1] != A[2]) printf("T\n");
        else printf("HL\n");
    } else {
        if(mx > sum - mx) printf("T\n");
        else if(sum & 1) printf("T\n");
        else printf("HL\n");
    }
}
 
int T;
 
int main() {
    scanf("%d", &T);
    while(T--) solve();
 
    return 0;
}