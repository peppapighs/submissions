#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 1e6 + 5;

int n, bt[N];
int mx[N], mn[N];
long A[N];

long solve(int l = 1, int r = n) {
    if(l == r) return 1;

    int mid = (l + r) >> 1;
    long ret = solve(l, mid) + solve(mid + 1, r);

    mx[mid] = mn[mid] = mid;    
    mx[mid + 1] = mn[mid + 1] = mid + 1;

    auto max_idx = [&](int a, int b) { return A[a] > A[b] ? a : b; };
    auto min_idx = [&](int a, int b) { return A[a] < A[b] ? a : b; };

    for(int i = mid - 1; i >= l; i--) {
        mx[i] = max_idx(i, mx[i + 1]);
        mn[i] = min_idx(i, mn[i + 1]);
    }
    for(int i = mid + 2; i <= r; i++) {
        mx[i] = max_idx(i, mx[i - 1]);
        mn[i] = min_idx(i, mn[i - 1]);
    }

    vector<int> cnt(70);
    for(int i = mid, r_mn = mid, r_mx = mid; i >= l; i--) {
        while(r_mx < r && A[mx[i]] >= A[mx[r_mx + 1]]) {
            ++cnt[bt[mn[r_mx + 1]]];
            ++r_mx;
        }
        while(r_mn < r_mx && A[mn[i]] < A[mn[r_mn + 1]]) {
            --cnt[bt[mn[r_mn + 1]]];
            ++r_mn;
        }
        ret += cnt[bt[mx[i]]];
        if(bt[mn[i]] == bt[mx[i]])
            ret += r_mn - mid;
    }
    cnt = vector<int>(70);
    for(int i = mid + 1, l_mn = mid + 1, l_mx = mid + 1; i <= r; i++) {
        while(l_mx > l && A[mx[i]] > A[mx[l_mx - 1]]) {
            ++cnt[bt[mn[l_mx - 1]]];
            --l_mx;
        }
        while(l_mn > l_mx && A[mn[i]] < A[mn[l_mn - 1]]) {
            --cnt[bt[mn[l_mn - 1]]];
            --l_mn;
        }
        ret += cnt[bt[mx[i]]];
        if(bt[mn[i]] == bt[mx[i]])
            ret += mid + 1 - l_mn;
    }

    return ret;
}

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        scanf("%lld", A + i);
        bt[i] = __builtin_popcountll(A[i]);
    }
    printf("%lld\n", solve());

    return 0;
}