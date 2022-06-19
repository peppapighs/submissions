#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 5e4 + 5;
const int B = 98765431;

int n, d;
map<long, int> mp[1 << 4];
vector<int> bit[5];
char S[N][4];

long get_hash(char *s, int b) {
    long ret = 0;
    for (int i = 0; i < 4; i++)
        if (b >> i & 1)
            ret = ret * B + s[i];
    return ret;
}

int main() {
    scanf("%d %d", &n, &d);
    for (int i = 0; i < (1 << 4); i++)
        bit[__builtin_popcount(i)].emplace_back(i);
    for (int i = 1; i <= n; i++) {
        scanf(" %s", S[i]);
        for (int j = 0; j < (1 << 4); j++)
            ++mp[j][get_hash(S[i], j)];
    }

    long ans = 0;
    for (int i = 1; i <= n; i++) {
        vector<long> sum(6);
        sum[0] = n - 1;
        for (int z = max(4 - d, 1); z <= min(4 - d + 1, 4); z++) {
            for (int st = 1; st < (1 << (int)bit[z].size()); st++) {
                int all = 0;
                for (int j = 0; j < (int)bit[z].size(); j++)
                    if (st >> j & 1)
                        all |= bit[z][j];
                int cnt = mp[all][get_hash(S[i], all)];
                if (__builtin_popcount(st) & 1)
                    sum[z] += cnt;
                else
                    sum[z] -= cnt;
            }
            --sum[z];
        }
        ans += sum[4 - d] - sum[4 - d + 1];
    }
    printf("%lld\n", ans / 2);

    return 0;
}