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

const int N = 3e3 + 5;

int n, k;
char A[N];

int main() {
    scanf("%d %d %s", &n, &k, A + 1);
    vector<int> a, b;
    for (int i = 1; i < n; i++)
        if (A[i] == 'R' && A[i + 1] == 'L')
            a.emplace_back(i);
    int cnt = 0;
    vector<vector<int>> op;
    while (!a.empty()) {
        op.emplace_back(vector<int>());
        cnt += a.size();
        for (int x : a) {
            A[x] = 'L', A[x + 1] = 'R';
            op.back().emplace_back(x);
            if (x > 1 && A[x - 1] == 'R')
                b.emplace_back(x - 1);
            if (x + 1 < n && A[x + 2] == 'L')
                b.emplace_back(x + 1);
        }
        a.clear();
        swap(a, b);
    }
    if (k < op.size() || k > cnt)
        return !printf("-1\n");
    int now = op.size();
    for (vector<int> &v : op) {
        while (now < k && v.size() > 1) {
            printf("1 %d\n", v.back());
            ++now;
            v.pop_back();
        }
        printf("%d ", (int)v.size());
        for (int x : v)
            printf("%d ", x);
        printf("\n");
    }

    return 0;
}