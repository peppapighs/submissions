#include <bits/stdc++.h>

using namespace std;

const int N = 1e4 + 5;

int n, l, q;
int A[N], Q[N], cnt[N][105];
vector<int> coord;

int get(int x) {
    return lower_bound(coord.begin(), coord.end(), x) - coord.begin() + 1;
}

int main() {
    scanf("%d %d", &n, &l);
    for (int i = 1; i <= n; i++)
        scanf("%d", A + i);
    scanf("%d", &q);
    for (int i = 1; i <= q; i++) {
        scanf("%d", Q + i);
        coord.emplace_back(Q[i]);
    }
    sort(coord.begin(), coord.end());
    coord.resize(unique(coord.begin(), coord.end()) - coord.begin());

    for (int dif = 1; dif <= n - l; dif++) {
        int match = 0;
        for (int i = 1; i <= l; i++)
            match += (A[i] == A[i + dif]);
        ++cnt[1][get(l - match)], ++cnt[dif + 1][get(l - match)];
        for (int i = l + 1, j = i + dif; j <= n; i++, j++) {
            if (A[i - l] == A[j - l])
                --match;
            if (A[i] == A[j])
                ++match;
            int idx = get(l - match);
            ++cnt[i - l + 1][idx], ++cnt[j - l + 1][idx];
        }
    }
    for (int i = 1; i <= n - l + 1; i++)
        for (int j = 1; j <= coord.size(); j++)
            cnt[i][j] += cnt[i][j - 1];
    for (int i = 1; i <= q; i++) {
        int idx = get(Q[i]);
        for (int j = 1; j <= n - l + 1; j++)
            printf("%d ", cnt[j][idx]);
        printf("\n");
    }

    return 0;
}