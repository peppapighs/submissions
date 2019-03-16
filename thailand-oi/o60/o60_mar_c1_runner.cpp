#include <bits/stdc++.h>

#define iii tuple<double, int, int>
#define long long long

using namespace std;

const int N = 2e3+5;
const int M = 2e5+5;

struct item {
    int y, idx;
    long l, r;
    item(int y, int idx, long l, long r) : y(y), idx(idx), l(l), r(r) { }
    friend bool operator<(const item &a, const item &b) {
        return a.y < b.y;
    }
};

int n, m, ptr, ans[M], pos[N], mp[N];
long v[N], t[N];
vector<item> Q;
vector<iii> inter;

int main() {
    iota(pos, pos+N, 0);

    scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; i++) scanf("%lld %lld", t+i, v+i);
    t[n+1] = v[n+1] = 1e10;

    for(int i = 1; i <= n; i++) for(int j = i+1; j <= n; j++) {
        long m1 = v[i], c1 = v[i] * t[i], m2 = v[j], c2 = v[j] * t[j];
        double yinter = (double)(c1 * m2 - c2 * m1) / (double)(m2 - m1);
        if(yinter > 0) inter.emplace_back(yinter, i, j);
    }

    for(int i = 1, a, b, c; i <= m; i++) {
        scanf("%d %d %d", &a, &b, &c); 
        Q.emplace_back(a, i, b, c);
    }

    sort(Q.begin(), Q.end());
    sort(inter.begin(), inter.end());
    sort(pos+1, pos+n+1, [&](const int &a, const int &b) {
        return t[a] < t[b];
    });

    for(int i = 1; i <= n; i++) mp[pos[i]] = i;

    for(item q : Q) {
        int y = q.y, idx = q.idx;
        long l = q.l, r = q.r;

        while(ptr < (int)inter.size() && get<0>(inter[ptr]) <= (double)y) {
            int a = get<1>(inter[ptr]), b = get<2>(inter[ptr]);
            swap(pos[mp[a]], pos[mp[b]]);
            swap(mp[a], mp[b]);
            ++ptr;
        }
        int L = 1, R = n;
        while(L < R) {
            int mid = (L + R) >> 1;
            double coord = (double)(y + v[mid] * t[mid]) / (double)v[mid];
            if(l <= coord) R = mid;
            else L = mid + 1;
        }
        int a = R;
        L = 1, R = n + 1;
        while(L < R) {
            int mid = (L + R) >> 1;
            double coord = (double)(y + v[mid] * t[mid]) / (double)v[mid];
            if(r < coord) R = mid;
            else L = mid + 1;
        }
        int b = R;
        ans[idx] = b - a;
    }
    for(int i = 1; i <= m; i++) printf("%d\n", ans[i]);

    return 0;
}