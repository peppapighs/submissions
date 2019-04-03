#include <bits/stdc++.h>

#define long long long
#define pii pair<long, long>
#define x first
#define y second

using namespace std;

const int N = 1e5+5;

long d(pii a, pii b) { return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y); }
long A(pii a, pii b, pii c) { return abs(a.x * b.y + b.x * c.y + c.x * a.y - b.x * a.y - c.x * b.y - a.x * c.y); }

int orient(pii a, pii b, pii c) {
    pii vec1(b.x - a.x, b.y - a.y);
    pii vec2(c.x - a.x, c.y - a.y);
    long now = (vec1.x * vec2.y) - (vec1.y * vec2.x);
    if(now == 0) return now;
    else return now < 0 ? 1 : 2;
}

void convex_hull(vector<pii> &V, vector<pii> &H) {
    sort(V.begin(), V.end(), [&](const pii &a, const pii &b) { return a.y < b.y; });
    sort(V.begin()+1, V.end(), [&](const pii &a, const pii &b) {
        int o = orient(V[0], a, b);
        if(o == 0) return d(V[0], a) < d(V[0], b);
        else return o == 1;
    });
    for(pii v : V) {
        while(H.size() > 2 && orient(H[H.size()-2], H[H.size()-1], v) != 1)
            H.pop_back();
        H.emplace_back(v);
    }
}

bool chk(pii v, vector<pii> &H) {
    if(v.y <= H[0].y) return v == H[0];
    int l = 1, r = H.size() - 2;
    while(l < r) {
        int m = (l + r + 1) >> 1;
        if(orient(H[0], H[m], v) < 2) l = m;
        else r = m - 1;
    }
    //Point lies inside triangle
    long all = A(H[0], H[l], H[l+1]);
    long a = A(v, H[l], H[l+1]);
    long b = A(H[0], v,  H[l+1]);
    long c = A(H[0], H[l], v);

    return (a + b + c == all);
}

int n, m, ans;
vector<pii> V1, V2, H1, H2;

int main() {
    scanf("%d %d", &n, &m);
    for(int i = 1, a, b; i <= n; i++) {
        scanf("%d %d", &a, &b);
        V1.emplace_back(a, b);
    }
    for(int i = 1, a, b; i <= m; i++) {
        scanf("%d %d", &a, &b);
        V2.emplace_back(a, b);
    }
    convex_hull(V1, H1), convex_hull(V2, H2);
    for(pii v : V1) ans += chk(v, H2);
    for(pii v : V2) ans += chk(v, H1);
    printf("%d\n", ans);

    return 0;
}
