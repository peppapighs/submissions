#include <bits/stdc++.h>

#define long long long
#define iii tuple<long, long, long>
#define pii pair<long, long>
#define x first
#define y second

using namespace std;

const int N = 2e3+5;

int n, s, H[N];
pii sel[N];
vector<iii> V;

long f(int mid) {
    int k = s - mid + 1;
    long ret = 0;
    fill_n(sel, N, pii(0, 0));
    for(iii &v : V) {
        long pre, h, idx;
        tie(pre, h, idx) = v;
        if(idx > mid) continue;
        if(!sel[idx].x && k - h >= 0)
            ret += pre, k -= h, sel[idx] = pii(pre, h);
        else if(sel[idx].x && h > sel[idx].y && k + sel[idx].y - h >= 0)
            ret += pre - sel[idx].x, k -= h - sel[idx].y, sel[idx] = pii(pre, h);
    } 
    return ret;
}

int main() {
    scanf("%d %d", &n, &s);
    for(int i = 1; i <= n; i++) {
        scanf("%d", H+i);
        for(int j = 1, pre = 0, a; j <= H[i]; j++) {
            scanf("%d", &a);
            pre += a;
            V.emplace_back(pre, j, i);
        }
    }
    sort(V.begin(), V.end(), [&](const iii &a, const iii &b) {
        return get<0>(a) * get<1>(b) >  get<0>(b) * get<1>(a);
    });
    int l = 1, r = n;
    for(int i = 1, sum = H[1]; i <= n; i++) {
        if(sum > s) break;
        sum += H[i+1] + 1, ++l;
    }
    while(r - l > 2) {
        int m1 = (l + l + r) / 3, m2 = (l + r + r) / 3;
        if(f(m1) <= f(m2)) l = m1 + 1;
        else r = m2 - 1;
    }
    long ret = 0;
    for(int i = l; i <= r; i++) ret = max(ret, f(i));
    printf("%lld\n", ret);

    return 0;
}