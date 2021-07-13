#include <bits/stdc++.h>
 
#define long long long
#define pii pair<long, long>
#define x first
#define y second
 
using namespace std;
 
const int N = 2.5e5 + 5;

struct FenwickTree {
    int t[N];

    void update(int x, int k) {
        for(int i = x; i < N; i += i & -i)
            t[i] += k;
    }

    int query(int x, int k = 0) {
        for(int i = x; i; i -= i & -i)
            k += t[i];
        return k;
    }
} tree;
 
int n, k;
int y[N], y_ord[N], l[N], r[N];
pii A[N];
vector<long> coord;
 
int get(long x) {
    return lower_bound(coord.begin(), coord.end(), x) - coord.begin() + 1;
}
 
int main() {
    iota(y_ord, y_ord + N, 0);

    scanf("%d %d", &n, &k);
 
    for(int i = 1; i <= n; i++) {
        long a, b;
        scanf("%lld %lld", &a, &b);
        A[i] = pii(a + b, a - b);
        coord.emplace_back(A[i].y);
    }
    sort(coord.begin(), coord.end());
    coord.resize(unique(coord.begin(), coord.end()) - coord.begin());
 
    sort(A + 1, A + n + 1);
    for(int i = 1; i <= n; i++)
        y[i] = get(A[i].y);

    sort(y_ord + 1, y_ord + n + 1, [&](int a, int b) {
        return A[a].y < A[b].y;
    });

    long dist = 0;
    for(int bit = 31; ~bit; bit--) {
        long now = dist | (1ll << bit), cnt = 0;

        for(int i = 1; i <= n; i++) {
            int lhs = l[y_ord[i - 1]];
            int rhs = r[y_ord[i - 1]];

            while(rhs + 1 <= coord.size() && coord[rhs] <= A[y_ord[i]].y + now)
                ++rhs;
            while(lhs + 1 <= coord.size() && coord[lhs] < A[y_ord[i]].y - now)
                ++lhs;
            
            l[y_ord[i]] = lhs, r[y_ord[i]] = rhs;
        }

        int j = 1;
        for(int i = 1; i <= n; i++) {
            while(j < i && A[i].x - A[j].x > now) {
                tree.update(y[j], -1); 
                ++j;
            }

            cnt += tree.query(r[i]) - tree.query(l[i]); 

            tree.update(y[i], 1);
        }
        for(; j <= n; j++) tree.update(y[j], -1);

        if(cnt < k) dist = now;
    }

    vector<long> ans;
    set<pii> st;
    for(int i = 1, j = 1; i <= n; i++) {
        while(j < i && A[i].x - A[j].x > dist) {
            st.erase(pii(A[j].y, j));
            ++j;
        }

        auto it = st.lower_bound(pii(A[i].y - dist, -1e18));

        while(it != st.end() && it->x <= A[i].y + dist) {
            long ta = A[i].x - A[it->y].x;
            long tb = A[i].y - A[it->y].y;

            ans.emplace_back(abs((ta + tb) / 2) + abs((ta - tb) / 2));

            ++it;
        }
        st.emplace(pii(A[i].y, i));
    }

    while(ans.size() < k) ans.emplace_back(dist + 1);
    sort(ans.begin(), ans.end());
    for(long x : ans) printf("%lld\n", x);
 
    return 0;
}