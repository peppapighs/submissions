#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 255;

void solve() {
    int r, c;
    char S[N][N];

    scanf("%d %d", &r, &c);

    vector<set<pii>> R(r), C(c);
    for (int i = 0; i < r; i++) {
        scanf(" %s", S[i]);
        for (int j = 0; j < c; j++)
            if (S[i][j] == 'R') {
                R[i].emplace(i, j);
                C[j].emplace(i, j);
            }
    }

    bool possible = false;
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            if (S[i][j] == '.')
                possible |= (R[i].empty() && C[j].empty());

    if (!possible) {
        printf("give up\n");
        return;
    }

    queue<pii> Q;
    for (int i = 0; i < r; i++)
        if (R[i].size() == 1)
            Q.emplace(*R[i].begin());
    for (int i = 0; i < c; i++)
        if (C[i].size() == 1)
            Q.emplace(*C[i].begin());

    while (!Q.empty()) {
        pii now = Q.front();
        Q.pop();
        R[now.x].erase(now);
        C[now.y].erase(now);
        if (R[now.x].size() == 1)
            Q.emplace(*R[now.x].begin());
        if (C[now.y].size() == 1)
            Q.emplace(*C[now.y].begin());
    }

    bool valid = true;
    for (int i = 0; i < r; i++)
        valid &= R[i].empty();
    for (int i = 0; i < c; i++)
        valid &= C[i].empty();

    if (valid)
        printf("there is hope\n");
    else
        printf("give up\n");
}

int T;

int main() {
    scanf("%d", &T);
    while (T--)
        solve();

    return 0;
}