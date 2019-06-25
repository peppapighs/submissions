#include <bits/stdc++.h>

#define long long long
#define pii pair<long, long>
#define x first
#define y second

using namespace std;

const int N = 1e6+5;

int n;
long A, B, cyc;
vector<pii> v;

int main() {
    scanf("%d %lld %lld", &n, &A, &B);
    cyc = A / __gcd(B+1, A);
    cyc *= B;

    for(int i = 1; i <= n; i++) {
        long l, r;
        scanf("%lld %lld", &l, &r);
        if(r - l + 1 >= cyc) v.emplace_back(0, 1), v.emplace_back(cyc, -1);
        else {
            l %= cyc, r %= cyc;
            v.emplace_back(l, 1);
            v.emplace_back(r + 1, -1); 
            if(l > r) {
                v.emplace_back(0, 1);
                v.emplace_back(cyc, -1);
            }
        }
    }
    sort(v.begin(), v.end());
    long ans = 0;
    for(int i = 0, cnt = 0; i < v.size(); ) {
        int j = i;
        for( ; v[i].x == v[j].x; j++) cnt += v[j].y;
        if(cnt) ans += v[j].x - v[i].x;
        i = j;
    }
    printf("%lld\n", ans);

    return 0;
}