#include "xylophone.h"
#include <bits/stdc++.h>

using namespace std;

const int N = 5e3 + 5;

int d1[N], d2[N], dir[N], ans[N];

void solve(int n) {
    for (int i = 1; i + 1 <= n; i++)
        d1[i] = query(i, i + 1);
    for (int i = 1; i + 2 <= n; i++)
        d2[i] = query(i, i + 2);

    dir[1] = 1;
    for (int i = 1; i + 2 <= n; i++) {
        if (d1[i] + d1[i + 1] == d2[i])
            dir[i + 1] = dir[i];
        else
            dir[i + 1] = -dir[i];
    }
    int mn = 1, mx = 1;
    for (int i = 1; i + 1 <= n; i++) {
        ans[i + 1] = ans[i] + dir[i] * d1[i];
        if (ans[i + 1] < ans[mn])
            mn = i + 1;
        if (ans[i + 1] > ans[mx])
            mx = i + 1;
    }
    int k = ans[mn];
    for (int i = 1; i <= n; i++) {
        ans[i] -= k - 1;
        if (mn > mx)
            ans[i] = n - ans[i] + 1;
        answer(i, ans[i]);
    }
}
