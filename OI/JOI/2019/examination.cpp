#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5+5;

vector<int> coord[N], t[N];

void update(vector<int> &t, int x, int k) {
    for(int i = x; i; i -= i & -i)
        t[i] += k;
}

int query(vector<int> &t, int x) {
    int ret = 0;
    for(int i = x; i < t.size(); i += i & -i) ret += t[i];
    return ret;
}

void update_2d(int x, int y, int k) {
    for(int i = x; i; i -= i & -i) {
        int idx = lower_bound(coord[i].begin(), coord[i].end(), y) - coord[i].begin() + 1;
        update(t[i], idx, k);
    }
}

int query_2d(int x, int y) {
    int ret = 0;
    for(int i = x; i < N; i += i & -i) {
        int idx = lower_bound(coord[i].begin(), coord[i].end(), y) - coord[i].begin() + 1;
        ret += query(t[i], idx);
    }
    return ret;
}

struct Query {
    int a, b, c, i;
    Query(int a, int b, int c, int i) : a(a), b(b), c(c), i(i) {}
    friend bool operator<(const Query &a, const Query &b) {
        return a.c > b.c;
    }
};

int n, q, ans[N];
vector<pii> st;
vector<Query> Q;

int main() {
    scanf("%d %d", &n, &q);

    vector<int> vec;
    function<int(int)> get = [&](int x) { return lower_bound(vec.begin(), vec.end(), x) - vec.begin() + 1; };
    for(int i = 1, a, b; i <= n; i++) {
        scanf("%d %d", &a, &b);
        st.emplace_back(a, b);
        vec.emplace_back(a);
    }
    sort(vec.begin(), vec.end());
    vec.resize(unique(vec.begin(), vec.end()) - vec.begin()); 

    for(pii p : st) for(int i = get(p.x); i; i -= i & -i) coord[i].emplace_back(p.y);
    for(int i = 1; i < N; i++) {
        sort(coord[i].begin(), coord[i].end());
        coord[i].resize(unique(coord[i].begin(), coord[i].end()) - coord[i].begin());
        t[i].resize(coord[i].size() + 5);
    }

    sort(st.begin(), st.end(), [&](pii &a, pii &b) {
        return a.x + a.y > b.x + b.y;
    });
    for(int i = 1, a, b, c; i <= q; i++) {
        scanf("%d %d %d", &a, &b, &c);
        Q.emplace_back(a, b, c, i);
    }
    sort(Q.begin(), Q.end());

    int ptr = 0;
    for(Query &ask : Q) {
        while(ptr < st.size() && st[ptr].x + st[ptr].y >= ask.c) {
            update_2d(get(st[ptr].x), st[ptr].y, 1);
            ptr++;
        }
        ans[ask.i] = query_2d(get(ask.a), ask.b);
    }
    for(int i = 1; i <= q; i++) printf("%d\n", ans[i]);

    return 0;
}