#include <bits/stdc++.h>

#define long long long
#define pii pair<long, long>
#define x first
#define y second

using namespace std;

const int N = 1e5+5;

int orient(pii a, pii b, pii c) {
    pii vec1(b.x - a.x, b.y - a.y);
    pii vec2(c.x - a.x, c.y - a.y);
    long cross = (vec1.x * vec2.y) - (vec2.x * vec1.y);
    if(cross == 0) return 0;
    else return cross > 0 ? 1 : 2;
}

void convex_hull(vector<pii> &V, pair<vector<pii>, vector<pii> > &H) {
    vector<pii> &T1 = H.x, &T2 = H.y;
    T1.emplace_back(V[0]), T1.emplace_back(V[1]);
    for(int i = 2; i < (int)V.size(); i++) {
        while(T1.size() > 1 && orient(T1[T1.size()-2], T1[T1.size()-1], V[i]) != 2)
            T1.pop_back();
        T1.emplace_back(V[i]);
    }
    T2.emplace_back(V[0]), T2.emplace_back(V[1]);
    for(int i = 2; i < (int)V.size(); i++) {
        while(T2.size() > 1 && orient(T2[T2.size()-2], T2[T2.size()-1], V[i]) != 1)
            T2.pop_back();
        T2.emplace_back(V[i]);
    }
}

int line(pii x, pii a, pii b) {
    double m = (double)(a.y - b.y) / (double)(a.x - b.x);
    double c = a.y - m * a.x;
    double now = m * x.x + c;
    if(now == (double)x.y) return 0;
    else return (double)x.y < now ? 1 : 2;
}

bool chk(pii x, pair<vector<pii>, vector<pii> > &H) {
    bool v1 = false, v2 = false;
    vector<pii> &high = H.x, &low = H.y;

    if(high[0].x > x.x || high.back().x < x.x) return false;
    
    auto it1 = lower_bound(high.begin(), high.end(), pii(x.x, -1e18));
    if(it1 != high.end()) {
        if(it1->x == x.x) v1 = (it1->y >= x.y);
        else v1 = (line(x, *prev(it1), *it1) != 2);
    }

    auto it2 = lower_bound(low.begin(), low.end(), pii(x.x, -1e18));
    if(it2 != low.end()) {
        if(it2->x == x.x) v2 = (it2->y <= x.y);
        else v2 = (line(x, *prev(it2), *it2) != 1);
    }
    
    return v1 & v2;
}

int n, m, ans;
vector<pii> V1, V2;
pair<vector<pii>, vector<pii> > H1, H2;

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
    sort(V1.begin(), V1.end()), sort(V2.begin(), V2.end());
    convex_hull(V1, H1), convex_hull(V2, H2);

    for(pii x : V1) ans += chk(x, H2);
    for(pii x : V2) ans += chk(x, H1);

    printf("%d\n", ans);

    return 0;
}