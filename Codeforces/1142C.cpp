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
    long cross = (vec1.x * vec2.y) - (vec1.y * vec2.x);
    if(cross == 0) return 0;
    return cross < 0 ? 1 : 2;
}

int n;
vector<pii> vec, ans;

int main() {
    scanf("%d", &n);
    for(int i = 1, a, b; i <= n; i++) {
        scanf("%d %d", &a, &b);
        vec.emplace_back(a, b - 1ll * a * a);
    }
    sort(vec.begin(), vec.end(), [&](const pii &a, const pii &b) {
        if(a.x == b.x) return a.y > b.y;
        return a.x < b.x;
    });
    for(int i = 0; i < n; i++) {
        if(i && vec[i].x == vec[i-1].x) continue;
        while(ans.size() > 1 && orient(ans[ans.size()-2], ans[ans.size()-1], vec[i]) != 1)
            ans.pop_back();
        ans.emplace_back(vec[i]);
    }
    printf("%d\n", ans.size() - 1);

    return 0;
}