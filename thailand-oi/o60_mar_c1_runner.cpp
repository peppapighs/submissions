#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 2e3+5;
const int M = 2e5+5;

struct query {
    int idx;
    long p, b, e;
    query(int idx, long p, long b, long e) : idx(idx), p(p), b(b), e(e) {}
    friend bool operator<(const query &a, const query &b) {
        return a.p < b.p;
    }
};

int n, m, ans[M];
long V[N], T[N];
vector<int> L;
vector<tuple<double, int, int> > P;
map<int, int> mp;
vector<query> Q;

int main() {
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; i++) scanf("%lld %lld", T+i, V+i);
    for(int i = 1; i <= n; i++) for(int j = i+1; j <= n; j++) {
        double yinter = (1.0*V[i]*V[j]*(T[j] - T[i])) / (1.0*(V[j] - V[i]));
        if(yinter >= 0) P.emplace_back(yinter, i, j);
    }
    sort(P.begin(), P.end());
    for(int i = 1; i <= n; i++) L.emplace_back(i);
    sort(L.begin(), L.end(), [&](const int &a, const int &b) {
        return T[a] < T[b];
    });
    for(int i = 0; i < n; i++) mp[L[i]] = i;
    for(int i = 1; i <= m; i++) {
        long p, b, e;
        scanf("%lld %lld %lld", &p, &b, &e);
        Q.emplace_back(i, p, b, e);
    }
    sort(Q.begin(), Q.end());
    int ptr = 0;
    for(query q : Q) {
        while(ptr < P.size() && get<0>(P[ptr]) <= q.p) {
            int a = get<1>(P[ptr]), b = get<2>(P[ptr]);
            swap(L[mp[a]], L[mp[b]]);
            swap(mp[a], mp[b]);
            ++ptr;
        }
        int hi, low;
        int l = 0, r = n-1;
        while(l < r) {
            int mid = (l + r + 1) >> 1;
            if(q.p + V[L[mid]]*T[L[mid]] <= q.e*V[L[mid]]) l = mid;
            else r = mid-1; 
        }
        hi = l, l = 0, r = n-1;
        while(l < r) {
            int mid = (l + r) >> 1;
            if(q.p + V[L[mid]]*T[L[mid]] >= q.b*V[L[mid]]) r = mid;
            else l = mid+1;
        }
        low = l;
        ans[q.idx] = hi - low + 1;
    }
    for(int i = 1; i <= m; i++) printf("%d\n", ans[i]);

    return 0;
}