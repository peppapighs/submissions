#include "wombats.h"
#include <bits/stdc++.h>

using namespace std;

const int N = 5e3 + 5;
const int M = 205;

int n, m;
int H[N][M], V[N][M], opt[M][M];

struct item {
    int dp[M][M];

    item() {}

    int *operator[](int x) { return dp[x]; }

    const int *operator[](int x) const { return dp[x]; };

    friend item operator+(const item &a, const item &b) {
        item ret;
        fill_n(ret.dp[0], M * M, INT_MAX);
        for (int i = 0; i < m; i++)
            for (int j = 0; j < m; j++)
                if (ret[0][i] > a[0][j] + b[j][i]) {
                    ret[0][i] = a[0][j] + b[j][i];
                    opt[0][i] = j;
                }
        // Paths don't cross, or else you can replace both paths with the
        // minimum one opt[i-1][j] <= opt[i][j] <= opt[i][j+1];
        for (int i = 1; i < m; i++) {
            opt[i][m] = m - 1;
            for (int j = m - 1; ~j; j--)
                for (int k = opt[i - 1][j]; k <= opt[i][j + 1]; k++)
                    if (ret[i][j] > a[i][k] + b[k][j]) {
                        ret[i][j] = a[i][k] + b[k][j];
                        opt[i][j] = k;
                    }
        }
        return ret;
    }
} t[1 << 10], tmp[10];

void newleaf(int p, int l, int r) {
    for (int k = l; k <= r; k++)
        for (int i = 0; i < m; i++)
            for (int j = 0; j < m; j++)
                tmp[k - l][i][j] = V[k][j] + abs(H[k][j] - H[k][i]);
    t[p] = tmp[0];
    for (int i = 1; i < r - l + 1; i++)
        t[p] = t[p] + tmp[i];
}

void build(int p = 1, int l = 0, int r = n - 1) {
    if (r - l + 1 <= 10)
        return void(newleaf(p, l, r));
    int mid = (l + r) >> 1;
    build(p << 1, l, mid), build(p << 1 | 1, mid + 1, r);
    t[p] = t[p << 1] + t[p << 1 | 1];
}

void update(int x, int p = 1, int l = 0, int r = n - 1) {
    if (r - l + 1 <= 10)
        return void(newleaf(p, l, r));
    int mid = (l + r) >> 1;
    if (x <= mid)
        update(x, p << 1, l, mid);
    else
        update(x, p << 1 | 1, mid + 1, r);
    t[p] = t[p << 1] + t[p << 1 | 1];
}

void init(int R, int C, int _H[5000][200], int _V[5000][200]) {
    n = R, m = C;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m - 1; j++)
            H[i][j + 1] = _H[i][j] + H[i][j];
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < m; j++)
            V[i][j] = _V[i][j];
    build();
}

void changeH(int P, int Q, int W) {
    int d = W - (H[P][Q + 1] - H[P][Q]);
    for (int i = Q + 1; i < m; i++)
        H[P][i] += d;
    update(P);
}

void changeV(int P, int Q, int W) {
    V[P][Q] = W;
    update(P);
}

int escape(int V1, int V2) { return t[1][V1][V2]; }
