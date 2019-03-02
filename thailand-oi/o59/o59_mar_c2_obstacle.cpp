#include <bits/stdc++.h>

#define long long long
#define iii tuple<long, long, long>
#define pii pair<long, long>
#define x first
#define y second

using namespace std;

const int N = 2e3+5;

int n, s, H[N];
vector<iii> V;

long f(int mid) {
    long ret = 0;
    int k = s - mid + 1;
    bool S[N];
    pii B[N];
    memset(S, 0, sizeof S);
    fill_n(B, N, pii(0, 0));
    for(int i = 0; i < V.size(); i++) {
        long pre, h, idx;
        tie(pre, h, idx) = V[i];
        if(idx > mid) continue;
        if(B[idx] == pii(0, 0) && k >= h) {
            ret += pre;
            B[idx] = pii(pre, h), S[i] = true;
        }
    } 
    if(k > 0) for(int i = 0; i < V.size(); i++) {
        if(S[i]) continue;
        long pre, h, idx;
        tie(pre, h, idx) = V[i];
        if(k >= h - B[idx].y) {
            ret += pre - B[idx].y;
            B[idx] = pii(pre, h); 
        }
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
    while(l < r) {
        int m = (l + r) >> 1;
        if(f(m) > f(m + 1)) r = m;
        else l = m+1;
    }
    printf("%lld\n", f(r));

    return 0;
}