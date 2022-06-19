#include "recoverlib.h"
#include <bits/stdc++.h>

using namespace std;

const int N = 3e3 + 5;

int n, A[N], cnt[N], lst[N];
bool chk[N];
vector<int> vec;

void solve(int l, int r, int d) {
    if (l == r)
        return void(chk[l] = true);
    int mid = (l + r) >> 1;
    if (recover_query(l, mid, d))
        solve(l, mid, d);
    if (recover_query(mid + 1, r, d))
        solve(mid + 1, r, d);
}

int main() {
    fill_n(A, N, 1), fill_n(lst, N, 1);
    n = recover_init();
    for (int i = 2; i < N; i++) {
        if (chk[i])
            continue;
        vec.emplace_back(i);
        for (int j = i + i; j < N; j += i)
            chk[j] = true;
    }
    for (int p : vec) {
        int d = p;
        while (recover_query(1, n, d)) {
            memset(chk, 0, sizeof chk);
            solve(1, n, d);
            for (int i = 1; i <= n; i++) {
                if (d == p)
                    cnt[i] += chk[i];
                if (chk[i])
                    A[i] *= p, lst[i] = p;
            }
            d *= p;
        }
    }
    for (int i = 1; i <= n; i++)
        if (cnt[i] == 1)
            A[i] *= lst[i];
    recover_answer(A);

    return 0;
}
