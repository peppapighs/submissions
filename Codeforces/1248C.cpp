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

const int M = 1e9+7;

int n, m;
long ans = 0;

long fibo(int x) {
    long a = 2, b = 0;
    long ret = 0;
    for(int i = 1; i <= x; i++) {
        long now = (a + b) % M;
        ret = (ret + a) % M;
        b = a, a = now;
    }
    return ret;
}


int main() { 
    int a, b;
    scanf("%d %d", &a, &b);
    if(a < b) swap(a, b);
    if(a == 1 && b == 1) printf("2\n");
    else printf("%lld\n", (2 + fibo(a - 1) + fibo(b - 1)) % M);

    return 0;
}