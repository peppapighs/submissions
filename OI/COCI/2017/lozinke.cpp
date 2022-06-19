#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 2e4 + 5;
const int P = 1e9 + 7;

int n, ans;
char S[N][15];
map<long, int> mp;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf(" %s", S[i] + 1);
        long hsh = 0;
        for (int j = 1; j <= strlen(S[i] + 1); j++)
            hsh = hsh * P + S[i][j];
        ++mp[hsh];
    }
    for (int i = 1; i <= n; i++) {
        int len = strlen(S[i] + 1);
        set<long> st;
        for (int j = 1; j <= len; j++) {
            long hsh = 0;
            for (int k = j; k <= len; k++) {
                hsh = hsh * P + S[i][k];
                if (st.find(hsh) == st.end()) {
                    ans += mp[hsh];
                    if (j == 1 && k == len)
                        --ans;
                    st.emplace(hsh);
                }
            }
        }
    }

    printf("%d\n", ans);

    return 0;
}