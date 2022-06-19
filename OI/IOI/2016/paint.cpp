#include "paint.h"
#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;

int n, k, w[N], b[N], sum[N];
bool pre[N][105], suf[N][105], black[N], white[N];
vector<int> c(1);

string solve_puzzle(string s, vector<int> _c) {
    n = s.length(), k = _c.size();
    s = '#' + s + '#';
    for (int i : _c)
        c.emplace_back(i);
    for (int i = 1; i <= n; i++) {
        w[i] += w[i - 1] + (s[i] == '_');
        b[i] += b[i - 1] + (s[i] == 'X');
    }
    pre[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        pre[i][0] = (b[i] == 0);
        for (int j = 1; j <= k; j++) {
            if (s[i] != 'X')
                pre[i][j] |= pre[i - 1][j];
            if (s[i] != '_' && i >= c[j] && s[i - c[j]] != 'X' &&
                w[i] == w[i - c[j]]) {
                if (j == 1)
                    pre[i][j] |= pre[i - c[j]][j - 1];
                else if (i > c[j])
                    pre[i][j] |= pre[i - c[j] - 1][j - 1];
            }
        }
    }

    suf[n + 1][k + 1] = suf[n + 2][k + 1] = 1;
    for (int i = n; i; i--) {
        suf[i][k + 1] = (b[n] == b[i - 1]);
        for (int j = k; j; j--) {
            if (s[i] != 'X')
                suf[i][j] |= suf[i + 1][j];
            if (s[i] != '_' && i + c[j] <= n + 1 && s[i + c[j]] != 'X' &&
                w[i - 1] == w[i + c[j] - 1])
                suf[i][j] |= suf[i + c[j] + 1][j + 1];
        }
    }

    for (int i = 1; i <= n; i++) {
        if (s[i] == '_')
            white[i] = 1;
        else
            for (int j = 0; j <= k; j++)
                white[i] |= (pre[i - 1][j] && suf[i + 1][j + 1]);
        if (s[i] == '_')
            continue;
        for (int j = 1; j <= k; j++)
            if (i >= c[j] && s[i - c[j]] != 'X' && s[i + 1] != 'X' &&
                w[i] == w[i - c[j]]) {
                if (!suf[i + 2][j + 1])
                    continue;
                if ((j == 1 && pre[i - c[j]][j - 1]) ||
                    (i > c[j] && pre[i - c[j] - 1][j - 1]))
                    ++sum[i - c[j] + 1], --sum[i + 1];
            }
    }
    string ans = "";
    for (int i = 1; i <= n; i++) {
        sum[i] += sum[i - 1];
        black[i] |= (sum[i] > 0);

        if (s[i] != '.')
            ans += s[i];
        else if (black[i] && white[i])
            ans += '?';
        else
            ans += black[i] ? 'X' : '_';
    }
    return ans;
}