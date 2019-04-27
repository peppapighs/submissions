#include "gondola.h"
#include <bits/stdc++.h>

#define long long long
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5+5;
const int M = 1e9+9;

int valid(int n, int A[]) {
    set<int> S(A, A + n);
    if((int)S.size() != n) return 0;
    for(int i = 0, k = -M; i < n; i++) if(A[i] <= n) {
        if(k == -M) k = (A[i] - i - 1 + n) % n;
        else if(k != (A[i] - i - 1 + n) % n) return 0;
    }
    return 1;
}

int replacement(int n, int A[], int ret[]) {
    int k = -M, ptr = 0, B[N];
    for(int i = 0; i < n; i++) if(A[i] <= n) k = (A[i] - i - 1 + n) % n;

    vector<pii> v;
    for(int i = 0; i < n; i++) {
        if(k == -M) B[i] = A[i];
        else B[i] = A[(i - k + n) % n];
        if(B[i] > n) v.emplace_back(B[i], i+1);
    }
    sort(v.begin(), v.end());
    for(int i = 0; i < (int)v.size(); i++) while(ptr + n < v[i].x) {
        ret[ptr++] = v[i].y;
        v[i].y = ptr + n;
    }
    return ptr;
}

long modpow(long a, long b) {
    long ret = 1;
    for( ; b; b >>= 1) {
        if(b & 1) ret = (ret * a) % M;
        a = (a * a) % M;
    }
    return ret;
}

int countReplacement(int n, int A[]) {
    if(!valid(n, A)) return 0;

    vector<int> v;
    for(int i = 0; i < n; i++) if(A[i] > n) v.emplace_back(A[i]);
    sort(v.begin(), v.end());

    long ans = 1;
    for(int i = 0; i < (int)v.size(); i++) {
        int b = v.size() - i;
        int p = v[i] - (i ? v[i-1] + 1 : n + 1);
        ans = (ans * modpow(b, p)) % M;
    }
    if((int)v.size() == n) ans = (ans * n) % M;

    return ans;
}