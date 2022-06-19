#include <bits/stdc++.h>

using namespace std;

const int N = 205;

struct node {
    int x, y, cl, bit;
    // int gem=0;
    node(int x, int y, int cl, int bit) : x(x), y(y), cl(cl), bit(bit) {}
    int gem() {
        int i = bit, ans = 0;
        while (i > 0) {
            ans += (i & 1);
            i = i >> 1;
        }
        return ans;
    }
};

int n, m, ptr, sx, sy;
char d[N][N];
int dp[N][N][6][1 << 7];
int dx[5] = {1, 0, -1, 0, 0};
int dy[5] = {0, 1, 0, -1, 0};

int main() {
    scanf("%d%d", &n, &m);
    for (int j = 0; j < n; j++) {
        string s;
        cin >> s;
        for (int i = 0; i < m; i++) {
            d[i][j] = s[i];
            if (d[i][j] == 'S') {
                sx = i, sy = j;
                d[i][j] = '.';
            }
            if (d[i][j] == 'G') {
                d[i][j] = 'A' + (ptr++);
            }
        }
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < 6; k++) {
                for (int l = 0; l < (1 << 7); l++) {
                    dp[i][j][k][l] = 2e9;
                }
            }
        }
    }
    queue<node> q;
    q.emplace(sx, sy, 0, 0);
    dp[sx][sy][0][0] = 0;
    while (!q.empty()) {
        node u = q.front();
        // printf("%d %d %d %d\n",u.x,u.y,u.cl,u.gem());
        q.pop();
        if (u.bit == (1 << 7) - 1) {
            printf("%d", dp[u.x][u.y][u.cl][u.bit]);
            return 0;
        }
        int cost = dp[u.x][u.y][u.cl][u.bit];
        for (int i = 0; i < 5; i++) {
            node v(u.x + dx[i], u.y + dy[i], (u.cl + 1) % 6, u.bit);
            if (v.x >= 0 && v.x < m && v.y >= 0 && v.y < n) {
                if (d[v.x][v.y] == '#')
                    continue;
                if ('0' <= d[v.x][v.y] && d[v.x][v.y] <= '9') {
                    int clock = d[v.x][v.y] - '0' - 1;
                    bool chk = v.gem() > clock || v.cl == clock;
                    if (chk && dp[v.x][v.y][v.cl][v.bit] > cost + 1) {
                        dp[v.x][v.y][v.cl][v.bit] = cost + 1;
                        q.push(v);
                    }
                } else if ('A' <= d[v.x][v.y] && d[v.x][v.y] <= 'Z') {
                    int b = d[v.x][v.y] - 'A';
                    v.bit |= (1 << b);
                    if (dp[v.x][v.y][v.cl][v.bit] > cost + 1) {
                        dp[v.x][v.y][v.cl][v.bit] = cost + 1;
                        q.push(v);
                    }
                } else if (dp[v.x][v.y][v.cl][v.bit] > cost + 1) {
                    dp[v.x][v.y][v.cl][v.bit] = cost + 1;
                    q.push(v);
                }
            }
        }
    }

    printf("-1");

    return 0;
}