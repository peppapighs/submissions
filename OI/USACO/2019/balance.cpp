#include <bits/stdc++.h>

#define long long long
#define pii pair<long, long>
#define x first
#define y second

using namespace std;

const int N = 1e5+5;

long cross(pii a, pii b, pii c) {
    pii vec1(b.x - a.x, b.y - a.y);
    pii vec2(c.x - a.x, c.y - a.y);
    return vec1.x * vec2.y - vec1.y * vec2.x;
}

int n;
long A[N];

int main() {
    freopen("balance.in", "r", stdin);
    freopen("balance.out", "w", stdout);

    scanf("%d", &n);
    vector<pii> vec;
    for(int i = 1; i <= n; i++) {
        scanf("%lld", A + i);
        A[i] *= 100000; 
    }
    vec.emplace_back(0, 0);
    for(int i = 1; i <= n + 1; i++) {
        while(vec.size() > 1 && cross(vec[vec.size() - 2], vec.back(), pii(i, A[i])) > 0)
            vec.pop_back();
        vec.emplace_back(i, A[i]);
    }
    int pre = -1;
    for(pii p : vec) {
        if(pre != -1) for(int i = pre + 1; i < p.x; i++)
            A[i] = (p.y * (i - pre) + A[pre] * (p.x - i)) / (p.x - pre);
        pre = p.x;
    }
    for(int i = 1; i <= n; i++) printf("%lld\n", A[i]);

    return 0;
}