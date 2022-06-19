#include "tile.h"
#include <bits/stdc++.h>

using namespace std;

const int N = 3e5 + 5;
const int B = 550;

int n, k;
int par[N][20];
vector<int> A;

void init(int _n, int _k, int _q, int _m, vector<int> _A) {
    n = _m, k = _k, A = _A;
    A.emplace_back(2e9);
    for (int i = n; ~i; i--) {
        if (i == n)
            par[i][0] = i;
        else
            par[i][0] = lower_bound(A.begin(), A.end(), A[i] + k) - A.begin();
        for (int j = 1; j <= 19; j++)
            par[i][j] = par[par[i][j - 1]][j - 1];
    }
}

int getNumberOfSpecialTiles(int l, int r) {
    auto it1 = lower_bound(A.begin(), A.end(), l),
         it2 = upper_bound(A.begin(), A.end(), r);
    if (it1 == it2)
        return 0;
    int a = it1 - A.begin(), b = it2 - A.begin(), ans = 0;
    for (int i = 19; ~i; i--)
        if (A[par[a][i]] < A[b])
            ans += (1 << i), a = par[a][i];
    return ans + 1;
}
