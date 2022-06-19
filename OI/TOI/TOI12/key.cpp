#include <bits/stdc++.h>

using namespace std;

string k1, k2;

bool check(string c) {
    int m = k1.length(), n = k2.length();
    if (m + n != c.length()) {
        return false;
    }
    bool dp[m + 1][n + 1];
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            dp[i][j] = false;
        }
    }

    for (int j = 0; j <= n; j++) {
        for (int i = 0; i <= m; i++) {
            if (i == 0 && j == 0) {
                dp[i][j] = true;
            } else if (i == 0 && k2[j - 1] == c[j - 1]) {
                dp[i][j] = dp[i][j - 1];
            } else if (j == 0 && k2[i - 1] == c[i - 1]) {
                dp[i][j] = dp[i - 1][j];
            } else if (k1[i - 1] == c[i + j - 1] && k2[j - 1] != c[i + j - 1]) {
                dp[i][j] = dp[i - 1][j];
            } else if (k2[j - 1] == c[i + j - 1] && k1[i - 1] != c[i + j - 1]) {
                dp[i][j] = dp[i][j - 1];
            } else if (k1[i - 1] == c[i + j - 1] && k2[j - 1] == c[i + j - 1]) {
                dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
            }
        }
    }
    return dp[m][n];
}

int main() {
    cin >> k1 >> k2;
    int q;
    scanf("%d", &q);
    while (q--) {
        string c;
        cin >> c;
        if (check(c)) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }

    return 0;
}
