#include <bits/stdc++.h>

#define long long long
#define pii pair<long, long>
#define x first
#define y second

using namespace std;

const int N = 1<<18;

struct quest {
        long T, a, b, c;
        quest(int T, int a, int b, int c) : T(T), a(a), b(b), c(c) {}
};

int n, q;
vector<quest> Q;
vector<long> V;
long t[N<<1];
pii lz[N<<1];

int get(long x) { return lower_bound(V.begin(), V.end(), x) - V.begin(); }

void push(int p, int l, int r) {
        if(lz[p].x) {
                t[p] = lz[p].y*(V[r+1] - V[l]);
                if(l != r) {
                        lz[p<<1] = lz[p];
                        lz[p<<1|1] = lz[p];
                }
                lz[p] = pii(0, 0);
        }
}

template<typename T>
void travel(int x, int y, const T &f, int p = 1, int l = 1, int r = V.size()-1) {
        push(p, l, r);
        if(x > r || l > y) return;
        if(x <= l && r <= y) return f(p, l, r);
        int m = (l + r) >> 1;
        travel(x, y, f, p<<1, l, m), travel(x, y, f, p<<1|1, m+1, r);
        t[p] = t[p<<1] + t[p<<1|1];
}

int main() {
        scanf("%d %d", &n, &q);
        V.emplace_back(-1);
        for(int i = 1; i <= q; i++) {
                long T, a, b, c;
                scanf("%lld %lld %lld", &T, &a, &b);
                if(T == 0) scanf("%lld", &c);
                Q.emplace_back(T, a, b, c);
                V.emplace_back(a), V.emplace_back(b);
        }

        sort(V.begin(), V.end());
        V.erase(unique(V.begin(), V.end()), V.end());

        for(quest q : Q) {
                long T = q.T, a = q.a, b = q.b, c = q.c;
                if(T == 0) travel(get(a), get(b)-1, [&](int p, int l, int r) {
                        lz[p] = pii(1, c);
                        push(p, l, r);
                });
                if(T == 1) {
                        long ret = 0;
                        travel(get(a), get(b)-1, [&](int p, int l, int r) {
                                ret += t[p];
                        });
                        printf("%lld\n", ret);
                }
        }

        return 0;
}
