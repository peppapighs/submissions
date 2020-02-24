#include <bits/stdc++.h>

#define long long long
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 2e5+5;

int n;
vector<pii> v;

int main() {
    scanf("%d", &n);
    for(int i = 1, a, b; i <= n; i++) {
        scanf("%d %d", &a, &b);
        v.emplace_back(a, b);
    }
    sort(v.begin(), v.end(), [&](pii a, pii b) {
        return a.x - a.y > b.x - b.y;
    });
    long l = 0, r = 1e18;
    while(l < r) {
        long mid = (l + r) >> 1;
        long now = mid;
        bool valid = true;
        for(pii p : v) {
            if(now < p.x) valid = false;
            now -= p.y;
            if(now < 0) valid = false;
        }
        if(valid) r = mid;
        else l = mid + 1;
    }
    printf("%lld\n", r);

    return 0;
}