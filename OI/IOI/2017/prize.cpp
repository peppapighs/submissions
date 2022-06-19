#include "prize.h"
#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> val;

vector<int> query(int i) {
    if (val[i][0] == -1)
        return val[i] = ask(i);
    return val[i];
}

bool valid(vector<int> vec) { return vec[0] + vec[1] == 0; }

void solve(int l, int r, vector<int> &L, vector<int> &R, int &ans) {
    if (r - l <= 1 || make_pair(L[0], L[1]) == make_pair(R[0], R[1]) || ~ans)
        return;

    int mid = (l + r) >> 1;
    vector<int> M = query(mid);
    if (valid(M))
        return void(ans = mid);

    if (L[0] + L[1] == R[0] + R[1] && M[0] + M[1] < L[0] + L[1] &&
        L[0] == R[0] - 1)
        return;

    solve(l, mid, L, M, ans), solve(mid, r, M, R, ans);
}

int find_best(int n) {
    val = vector<vector<int>>(n, vector<int>(2, -1));

    vector<int> l = query(0), r = query(n - 1);
    if (valid(l))
        return 0;
    if (valid(r))
        return n - 1;

    int ans = -1;
    solve(0, n - 1, l, r, ans);

    return ans;
}
