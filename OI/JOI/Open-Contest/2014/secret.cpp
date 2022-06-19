#include "secret.h"
#include <bits/stdc++.h>

using namespace std;

const int N = 1 << 10;

int n;
int L[N][12], R[N][12];

void Init(int _n, int A[]) {
    n = _n;

    function<void(int, int, int)> build = [&](int lvl, int l, int r) {
        if (l == r)
            return void(L[l][lvl] = R[l][lvl] = A[l]);

        int mid = (l + r) >> 1;
        L[mid][lvl] = A[mid], R[mid + 1][lvl] = A[mid + 1];
        for (int i = mid - 1; i >= l; i--)
            L[i][lvl] = Secret(A[i], L[i + 1][lvl]);
        for (int i = mid + 2; i <= r; i++)
            R[i][lvl] = Secret(R[i - 1][lvl], A[i]);

        build(lvl + 1, l, mid), build(lvl + 1, mid + 1, r);
    };
    build(0, 0, n - 1);
}

int Query(int x, int y) {
    function<int(int, int, int)> query = [&](int lvl, int l, int r) {
        if (l == r)
            return L[l][lvl];

        int mid = (l + r) >> 1;
        if (x <= mid && mid + 1 <= y)
            return Secret(L[x][lvl], R[y][lvl]);
        if (y <= mid)
            return query(lvl + 1, l, mid);
        return query(lvl + 1, mid + 1, r);
    };
    return query(0, 0, n - 1);
}
