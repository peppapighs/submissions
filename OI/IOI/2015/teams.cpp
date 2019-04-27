#include "teams.h"
#include <bits/stdc++.h>

using namespace std;

const int N = 5e5+5;

int n, rot[N];
vector<int> t, L, R;

int newleaf(int d) {
    t.emplace_back(d);
    L.emplace_back(-1), R.emplace_back(-1);
    return t.size() - 1;
}

int newpar(int l, int r) {
    t.emplace_back(t[l] + t[r]);
    L.emplace_back(l), R.emplace_back(r);
    return t.size() - 1;
}

int build(int l = 0, int r = N-1) {
    if(l == r) return newleaf(0);
    int mid = (l + r) >> 1;
    return newpar(build(l, mid), build(mid+1, r));
}

int update(int x, int p, int l = 0, int r = N-1) {
    if(l == r) return newleaf(t[p] + 1);
    int mid = (l + r) >> 1;
    if(x <= mid) return newpar(update(x, L[p], l, mid), R[p]);
    else return newpar(L[p], update(x, R[p], mid+1, r));
}

int remove(int k, int p, int pz, int l = 0, int r = N-1) {
    if(r <= k) return pz;
    if(l > k) return p;
    int mid = (l + r) >> 1;
    return newpar(remove(k, L[p], L[pz], l, mid), remove(k, R[p], R[pz], mid+1, r));
}

int choose(int k, int all, int p, int l = 0, int r = N-1) {
    if(l == r) return newleaf(t[p] + k);
    int sum = t[L[all]] - t[L[p]], mid = (l + r) >> 1;
    if(sum >= k) return newpar(choose(k, L[all], L[p], l, mid), R[p]);
    else return newpar(L[all], choose(k - sum, R[all], R[p], mid+1, r));
}

int start;
vector<int> coord[N];

void init(int _n, int A[], int B[]) {
    n = _n, rot[0] = build();
    for(int i = 0; i < n; i++) coord[A[i]].emplace_back(B[i]);
    for(int i = 1; i <= n; i++) {
        rot[i] = remove(i-1, rot[i-1], rot[0]);
        for(int b : coord[i]) rot[i] = update(b, rot[i]);
    }
    start = build(); 
}

int can(int m, int K[]) {
    sort(K, K+m);
    int cur = start;
    for(int i = 0; i < m; i++) {
        cur = remove(K[i]-1, cur, rot[0]);
        if(t[rot[K[i]]] - t[cur] < K[i]) return 0;
        cur = choose(K[i], rot[K[i]], cur);
    }
    return 1;
}