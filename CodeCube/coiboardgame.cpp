#include <bits/stdc++.h>

using namespace std;

struct node {
    int x, y, bit;
    node(int x, int y, int bit) : x(x), y(y), bit(bit) {}
};

const int N = 505;

int n, m, sx, sy, ex, ey;
char d[N][N];
int v[N][N][1 << 3];
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

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
            if (d[i][j] == 'E') {
                ex = i, ey = j;
                d[i][j] = '.';
            }
        }
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < (1 << 3); k++) {
                v[i][j][k] = 2e9;
            }
        }
    }
    queue<node> q;
    q.emplace(sx, sy, 0);
    v[sx][sy][0] = 0;
    while (!q.empty()) {
        node f = q.front();
        int cost = v[f.x][f.y][f.bit];
        // printf("%d %d %d : %d\n",f.x,f.y,f.bit,cost);
        q.pop();
        for (int i = 0; i < 4; i++) {
            if (f.x + dx[i] >= 0 && f.x + dx[i] < m && f.y + dy[i] >= 0 &&
                f.y + dy[i] < n) {
                node u(f.x + dx[i], f.y + dy[i], f.bit);
                if (d[u.x][u.y] != '#') {
                    if (d[u.x][u.y] >= 'a' && d[u.x][u.y] <= 'z') {
                        if (d[u.x][u.y] == 'j')
                            u.bit |= 1;
                        else if (d[u.x][u.y] == 'b')
                            u.bit |= 2;
                        else if (d[u.x][u.y] == 'p')
                            u.bit |= 4;
                        if (v[u.x][u.y][u.bit] > cost + 1) {
                            v[u.x][u.y][u.bit] = cost + 1;
                            q.push(u);
                        }
                    } else if (d[u.x][u.y] >= 'A' && d[u.x][u.y] <= 'Z') {
                        bool chk = false;
                        if (d[u.x][u.y] == 'J' && u.bit & 1)
                            chk = true;
                        else if (d[u.x][u.y] == 'B' && (u.bit >> 1) & 1)
                            chk = true;
                        else if (d[u.x][u.y] == 'P' && (u.bit >> 2) & 1)
                            chk = true;
                        if (chk && v[u.x][u.y][u.bit] > cost + 1) {
                            v[u.x][u.y][u.bit] = cost + 1;
                            q.push(u);
                        }
                    } else {
                        if (v[u.x][u.y][u.bit] > cost + 1) {
                            v[u.x][u.y][u.bit] = cost + 1;
                            q.push(u);
                        }
                    }
                }
            }
        }
    }

    int ans = 2e9;

    for (int i = 0; i < (1 << 3); i++) {
        // printf("%d %d\n",v[ex][ey][i],i);
        ans = min(ans, v[ex][ey][i]);
    }
    if (ans == 2e9)
        printf("-1");
    else
        printf("%d", ans);

    return 0;
}