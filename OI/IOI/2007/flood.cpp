#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;

int n, w, dir[N][4];
int X[N], Y[N], pos[N];
int A[N], B[N], chk[N][2];

int main() {
    iota(pos, pos + N, 0);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d %d", X + i, Y + i);
    scanf("%d", &w);
    for (int i = 1; i <= w; i++) {
        scanf("%d %d", A + i, B + i);
        if (X[A[i]] > X[B[i]] || Y[A[i]] > Y[B[i]])
            swap(A[i], B[i]);
        if (X[A[i]] == X[B[i]])
            dir[A[i]][2] = i, dir[B[i]][0] = i;
        else
            dir[A[i]][1] = i, dir[B[i]][3] = i;
    }
    sort(pos + 1, pos + n + 1, [&](const int &a, const int &b) {
        return make_pair(X[a], Y[a]) < make_pair(X[b], Y[b]);
    });
    for (int i = 1, idx; i <= n; i++) {
        while (1) {
            bool valid = false;
            int u = pos[i], d = 0;
            for (int j = 0; j < 4; j++) {
                int nex = dir[u][j];
                valid |= (nex && !chk[nex][j < 2]);
            }
            if (!valid)
                break;
            ++idx;
            vector<int> add;
            do {
                int nex, nd;
                for (int j = 0; j < 4; j++) {
                    nd = (d + j + 3) % 4;
                    nex = dir[u][nd];
                    if (nex && !chk[nex][nd < 2]) {
                        u = A[nex] + B[nex] - u, d = nd;
                        chk[nex][nd < 2] = idx;
                        add.emplace_back(nex);
                        break;
                    }
                }
            } while (u != pos[i]);
            for (int id : add) {
                if (!chk[id][0])
                    chk[id][0] = -1;
                if (!chk[id][1])
                    chk[id][1] = -1;
            }
        }
    }
    vector<int> ans;
    for (int i = 1; i <= w; i++)
        if (chk[i][0] == chk[i][1])
            ans.emplace_back(i);
    printf("%d\n", (int)ans.size());
    for (int i : ans)
        printf("%d\n", i);

    return 0;
}