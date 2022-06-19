#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e6 + 5;

int R, C, d, k, ans;
vector<pii> mush;

int main() {
    scanf("%d %d %d %d", &R, &C, &d, &k);
    vector<vector<int>> A(R + 2, vector<int>(C + 2));
    for (int i = 1; i <= R; i++) {
        char S[N];
        scanf(" %s", S + 1);
        for (int j = 1; j <= C; j++) {
            if (S[j] == 'M')
                mush.emplace_back(i, j);
            else if (S[j] == 'S') {
                int tr = max(i - d, 1), tc = max(j - d, 1);
                int br = min(i + d + 1, R + 1), bc = min(j + d + 1, C + 1);
                ++A[tr][tc], --A[tr][bc], --A[br][tc], ++A[br][bc];
            }
        }
    }
    for (int i = 1; i <= R; i++)
        for (int j = 1; j <= C; j++)
            A[i][j] += A[i - 1][j] + A[i][j - 1] - A[i - 1][j - 1];
    for (pii m : mush)
        if (A[m.x][m.y] >= k)
            ++ans;
    printf("%d\n", ans);

    return 0;
}