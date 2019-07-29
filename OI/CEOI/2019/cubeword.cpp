#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 62;
const int M = 998244353;
const char base[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

int n, f[256];
long pre[12][N][N], dp[12][N][N][N], perm[2][2][2];
vector<string> S[12];

long get(int sz, int a, int b, int c, int d) {
    long ret = dp[sz][a][b][c] * dp[sz][a][b][d] % M * dp[sz][a][c][d] % M * dp[sz][b][c][d] % M;
    ret = ret * perm[a == b][b == c][c == d] % M;
    return ret;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    for(int i = 0; i < N; i++) f[base[i]] = i;
    for(int i = 0; i < 4; i++) for(int j = i; j < 4; j++) for(int k = j; k < 4; k++) for(int l = k; l < 4; l++) {
        set<vector<int> > st;
        vector<int> now = {i, j, k, l};
        do st.emplace(now);
        while(next_permutation(now.begin(), now.end()));
        perm[i == j][j == k][k == l] = st.size();
    }

    cin >> n;
    for(int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        S[s.size()].emplace_back(s);
        reverse(s.begin(), s.end());
        S[s.size()].emplace_back(s);
    } 
    for(int i = 3; i <= 11; i++) {
        sort(S[i].begin(), S[i].end());
        S[i].resize(unique(S[i].begin(), S[i].end()) - S[i].begin());
        for(string s : S[i]) ++pre[i][f[s[0]]][f[s.back()]];
    }
    for(int sz = 3; sz <= 11; sz++)
        for(int i = 0; i < N; i++) for(int j = i; j < N; j++) for(int k = j; k < N; k++)
            for(int l = 0; l < N; l++)
                dp[sz][i][j][k] = (dp[sz][i][j][k] + pre[sz][i][l] * pre[sz][j][l] * pre[sz][k][l] % M) % M;

    long ans = 0;
    for(int sz = 3; sz <= 11; sz++)
        for(int i = 0; i < N; i++) for(int j = i; j < N; j++) for(int k = j; k < N; k++)
            for(int l = k; l < N; l++)
                ans = (ans + get(sz, i, j, k, l)) % M;
    cout << ans << "\n";

    return 0;
}