#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

#define var int p = 1, int l = 1, int r = n
#define mid ((l + r) >> 1)
#define lb p<<1, l, mid
#define rb p<<1|1, mid+1, r

const int N = 1<<17;

int n;

struct seg_tree {
    int t[N<<1];

    void clear() { memset(t, 0, sizeof t); }

    void update(int x, int k, var) {
        if(l == r) return void(t[p] += k);
        if(x <= mid) update(x, k, lb);
        else update(x, k, rb);
        t[p] = t[p<<1] + t[p<<1|1];
    }

    int query(int x, int y, var) {
        if(x > r || l > y) return 0;
        if(x <= l && r <= y) return t[p];
        return query(x, y, lb) + query(x, y, rb);
    }

    int get_pos(int k, var) {
        if(l == r) return l;
        if(t[p<<1] <= k) return get_pos(k - t[p<<1], rb);
        else return get_pos(k, lb);
    }
} L, R;

vector<pii> vec;
vector<int> coord;

bool chk(int k) {
    L.clear(), R.clear();
    for(int i = 1; i <= n; i++) R.update(vec[i-1].y, 1);
    for(int i = 1, j; i <= n; ) {
        for(j = i; vec[j-1].x == vec[i-1].x; j++) {
            L.update(vec[j-1].y, 1);
            R.update(vec[j-1].y, -1);
        }
        int now = min(L.get_pos(k), R.get_pos(k));
        if(L.query(now, n) <= k && R.query(now, n) <= k) return true;
        i = j;
    }
    return false;
}

int main() {
    freopen("balancing.in", "r", stdin);
    freopen("balancing.out", "w", stdout);

    scanf("%d", &n);
    for(int i = 1, a, b; i <= n; i++) {
        scanf("%d %d", &a, &b);
        vec.emplace_back(a, b);
        coord.emplace_back(b);
    }
    sort(vec.begin(), vec.end()), sort(coord.begin(), coord.end());
    coord.resize(unique(coord.begin(), coord.end()) - coord.begin());

    for(int i = 1; i <= n; i++) 
        vec[i-1].y = lower_bound(coord.begin(), coord.end(), vec[i-1].y) - coord.begin() + 1;

    int l = 0, r = n;
    while(l < r) {
        if(chk(mid)) r = mid;
        else l = mid + 1;
    }
    printf("%d\n", r);

    return 0;
}