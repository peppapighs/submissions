#include <bits/stdc++.h>

#define iii tuple<int, int, int>
#define long long long

using namespace std;

const int N = 8e4 + 5;
const int M = 1e6 + 5;

int n, t, p, block, freq[M];
long A[N], ans[N], sum;
vector<long> f[M];

void update(int i, bool del) {
    sum = (sum - (freq[A[i]] * f[A[i]][freq[A[i]]]) % p + p) % p;
    if (del)
        --freq[A[i]];
    else
        ++freq[A[i]];
    sum = (sum + (freq[A[i]] * f[A[i]][freq[A[i]]]) % p + p) % p;
}

int main() {
    scanf("%d %d %d", &n, &t, &p);
    block = (int)sqrt(n);

    for (int i = 0; i < n; i++) {
        scanf("%lld", A + i);
        if (f[A[i]].empty())
            f[A[i]].emplace_back(1);
        f[A[i]].emplace_back((f[A[i]].back() * A[i]) % p);
    }
    f[0].emplace_back(0);

    vector<vector<iii>> vec(block + 1);
    for (int i = 1, a, b; i <= t; i++) {
        scanf("%d %d", &a, &b);
        --a, --b;
        vec[a / block].emplace_back(a, b, i);
    }
    for (int i = 0; i <= block; i++) {
        sort(vec[i].begin(), vec[i].end(),
             [&](const iii &a, const iii &b) { return get<1>(a) < get<1>(b); });
        int L = i * block, R = i * block;
        sum = 0;
        for (iii q : vec[i]) {
            int a, b, idx;
            tie(a, b, idx) = q;
            while (R <= b)
                update(R++, 0);
            while (L > a)
                update(--L, 0);
            while (L < a)
                update(L++, 1);
            ans[idx] = sum;
        }
        while (L < R)
            --freq[A[L++]];
    }
    for (int i = 1; i <= t; i++)
        printf("%lld\n", ans[i]);

    return 0;
}