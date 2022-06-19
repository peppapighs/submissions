#include <bits/stdc++.h>

#define long long long

using namespace std;

char S[20], ans[20];
long rnk, fac[20];

int main() {
    fac[0] = 1;
    for (int i = 1; i < 20; i++)
        fac[i] = fac[i - 1] * i;

    while (scanf(" %s %lld", S, &rnk), S[0] != '#') {
        int n = strlen(S);
        vector<int> cnt(26);
        for (int i = 0; i < n; i++)
            ++cnt[S[i] - 'A'];

        long sum = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 26; j++)
                if (cnt[j]) {
                    long add = fac[n - i - 1];
                    for (int k = 0; k < 26; k++)
                        add /= fac[cnt[k] - (k == j)];
                    if (sum + add >= rnk) {
                        ans[i] = 'A' + j;
                        --cnt[j];
                        break;
                    } else
                        sum += add;
                }
        }
        ans[n] = '\0';
        printf("%s\n", ans);
    }

    return 0;
}