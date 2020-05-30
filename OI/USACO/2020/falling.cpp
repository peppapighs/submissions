#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 2e5+5;

struct line {
    long m, c; int idx;
    line() {}
    line(long m, long c, int idx) : m(m), c(c), idx(idx) {}
    friend bool operator<(const line &a, const line &b) {
        return a.c < b.c;
    }
};

bool bad(line a, line b, line c) {
    return (a.m - b.m) * (c.c - a.c) > (a.m - c.m) * (b.c - a.c);
}

int n, Q[N];
line A[N];
long num[N], den[N];

template<typename T>
void solve(vector<line> &vec, const T &f) {
    vector<line> hull;
    for(int i = 0; i < vec.size(); i++) {
        while(!hull.empty() && f(hull.back().m, vec[i].m))
            hull.pop_back();
        while(hull.size() > 1 && bad(hull[hull.size() - 2], hull.back(), vec[i]))
            hull.pop_back();
        hull.emplace_back(vec[i]);
        int now = vec[i].idx;
        if(f(vec[i].c, A[Q[now]].c)) {
            if(f(hull[0].m, -Q[now])) {
                num[now] = -1;
                continue;
            }
            int l = 0, r = hull.size() - 1;
            while(l < r) {
                int mid = (l + r) >> 1;
                if(bad(hull[mid], hull[mid + 1], A[Q[now]])) r = mid;
                else l = mid + 1;
            }
            long hi = abs(A[Q[now]].c - hull[r].c), lo = abs(A[Q[now]].m - hull[r].m);
            long g = __gcd(hi, lo);
            num[now] = hi / g, den[now] = lo / g;
        }
    } 
}

vector<line> vec;

int main() {
    freopen("falling.in", "r", stdin);
    freopen("falling.out", "w", stdout);

    scanf("%d", &n);
    for(int i = 1, a; i <= n; i++) {
        scanf("%d", &a);
        A[i] = line(-i, a, i);
        vec.emplace_back(-i, a, i);
    }
    for(int i = 1; i <= n; i++) scanf("%d", Q + i);

    sort(vec.begin(), vec.end());
    solve(vec, less<long>());

    reverse(vec.begin(), vec.end());
    solve(vec, greater<long>());
    
    for(int i = 1; i <= n; i++) {
        if(num[i] == -1) printf("-1\n");
        else printf("%lld/%lld\n", num[i], den[i]);
    }

    return 0;
}