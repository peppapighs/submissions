#include "holiday.h"
#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 1e5 + 5;

int ptr;
long t1[N * 20], t2[N * 20];
int L[N * 20], R[N * 20];

int newleaf(long sum, long cnt) {
    t1[ptr] = sum, t2[ptr] = cnt;
    L[ptr] = -1, R[ptr] = -1;
    return ptr++;
}

int newpar(int l, int r) {
    t1[ptr] = t1[l] + t1[r], t2[ptr] = t2[l] + t2[r];
    L[ptr] = l, R[ptr] = r;
    return ptr++;
}

int n, d, start, a[N], ver[N];
long ans = -1;
vector<int> coord;
map<int, int> M;

int build(int l = 1, int r = n) {
    if (l == r)
        return newleaf(0, 0);
    int mid = (l + r) >> 1;
    return newpar(build(l, mid), build(mid + 1, r));
}

int update(int x, long k, int p, int l = 1, int r = n) {
    if (l == r)
        return newleaf(k, 1);
    int mid = (l + r) >> 1;
    if (x <= mid)
        return newpar(update(x, k, L[p], l, mid), R[p]);
    else
        return newpar(L[p], update(x, k, R[p], mid + 1, r));
}

long query(int k, int pl, int pr, int l = 1, int r = n) {
    if (!k)
        return 0;
    if (l == r)
        return t1[pr] - t1[pl];
    long sum_r = t1[R[pr]] - t1[R[pl]], cnt_r = t2[R[pr]] - t2[R[pl]];
    int mid = (l + r) >> 1;
    if (cnt_r >= k)
        return query(k, R[pl], R[pr], mid + 1, r);
    else
        return sum_r + query(k - cnt_r, L[pl], L[pr], l, mid);
}

void solve(int l, int r, int optl, int optr) {
    if (l > r)
        return;
    long now = -1, idx = optl;
    int mid = (l + r) >> 1;
    for (int i = max(mid + 1, optl); i <= min(mid + d - 1, optr); i++) {
        int cost = i - mid + min(abs(start - i), abs(start - mid));
        if (d - cost - 2 < 0)
            continue;
        long q = query(d - cost - 2, ver[mid], ver[i - 1]) + a[mid] + a[i];
        if (q > now)
            now = q, idx = i;
    }
    ans = max(ans, now);
    solve(l, mid - 1, optl, idx), solve(mid + 1, r, idx, optr);
}

long findMaxAttraction(int _n, int _start, int _d, int _a[]) {
    n = _n, start = _start + 1, d = _d;
    for (int i = 1; i <= n; i++) {
        a[i] = _a[i - 1];
        coord.emplace_back(a[i]);
    }
    if (d == 1)
        return a[start];
    sort(coord.begin(), coord.end());
    ver[0] = build();
    for (int i = 1; i <= n; i++) {
        int idx = lower_bound(coord.begin(), coord.end(), a[i]) -
                  coord.begin() + ++M[a[i]];
        ver[i] = update(idx, a[i], ver[i - 1]);
    }
    for (int i = max(1, start - d + 1); i <= min(n, start + d - 1); i++)
        ans = max(ans, (long)a[i]);
    solve(max(1, start - d), min(n, start + d), 1, n);

    return ans;
}