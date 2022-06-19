#include <bits/stdc++.h>

using namespace std;

struct coord {
    int x, y;
    int dis = 0;
};

int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};

int main() {
    int m, n;
    scanf("%d %d", &n, &m);
    char table[m][n];
    vector<vector<bool>> visited(m, vector<bool>(n, false));
    queue<coord> q;
    for (int j = 0; j < n; j++) {
        string s;
        cin >> s;
        for (int i = 0; i < m; i++) {
            table[i][j] = s[i];
            if (s[i] == 'X') {
                coord t;
                t.x = i;
                t.y = j;
                q.push(t);
                visited[i][j] = true;
            }
        }
    }

    int res1 = 0, res2 = 0;

    while (!q.empty()) {
        coord t;
        t.x = q.front().x;
        t.y = q.front().y;
        t.dis = q.front().dis;
        q.pop();
        for (int i = 0; i < 4; i++) {
            coord c;
            c.x = t.x + dx[i];
            c.y = t.y + dy[i];
            c.dis = t.dis + 1;

            if (c.x >= 0 && c.x < m && c.y >= 0 && c.y < n &&
                table[c.x][c.y] != 'W' && !visited[c.x][c.y]) {
                visited[c.x][c.y] = true;
                q.push(c);
            }
        }
        if (table[t.x][t.y] == 'A') {
            res1++;
            res2 += t.dis;
        }
    }

    printf("%d %d", res1, res2 * 2);

    return 0;
}
