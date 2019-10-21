#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

#define long long long
#define iii tuple<int, int, int>
#define pii pair<long, long>
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

const int N = 1 << 9;

int n;
int A[N];
char S[N];

int check(int a, int b) {
    swap(A[a], A[b]);
    int mn = 1e9, idx = -1;
    for(int i = 1, cnt = 0; i <= n; i++) {
        cnt += A[i];
        if(cnt < mn) mn = cnt, idx = i;
    }
    int ans = 0, book = 0;
    for(int i = 1; i <= n; i++) {
        if(mn + book >= 0) ++ans;
        book -= A[i];
    }
    swap(A[a], A[b]);
    return ans;
}

int main() {
    scanf("%d %s", &n, S + 1);
    int sum = 0;
    for(int i = 1; i <= n; i++) {
        if(S[i] == '(') ++sum, A[i] = 1;
        else --sum, A[i] = -1;
    }
    if(sum != 0) return !printf("0\n1 1\n");
    int mx = -1, a = -1, b = -1;
    for(int i = 1; i <= n; i++) for(int j = i; j <= n; j++) {
        int now = check(i, j);
        if(now > mx) mx = now, a = i, b = j;
    }
    printf("%d\n%d %d\n", mx, a, b);

    return 0;
}