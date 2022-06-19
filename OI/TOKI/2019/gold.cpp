#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

int r, c, q, dist[4];
pii cand[4];

int ask(pii a, int ret = 0) {
    printf("? %d %d\n", a.x, a.y), fflush(stdout);
    scanf("%d", &ret);
    return ret;
}

int main() {
    scanf("%d %d %d", &r, &c, &q);

    vector<pii> p = {{1, 1}, {1, c}, {r, c}, {r, 1}};
    for (int i = 0; i < 4; i++)
        dist[i] = ask(p[i]);

    cand[0].x = (dist[0] + dist[1] - c + 3) / 2;
    cand[0].y = dist[0] - cand[0].x + 2;
    cand[1].x = (dist[1] - dist[2] + r + 1) / 2;
    cand[1].y = r - cand[1].x + c - dist[2];
    cand[2].y = (dist[3] - dist[2] + c + 1) / 2;
    cand[2].x = r + c - dist[2] - cand[2].y;
    cand[3].x = (dist[0] - dist[3] + r + 1) / 2;
    cand[3].y = dist[0] + 2 - cand[3].x;

    bool valid = false;
    if (1 <= cand[0].x && cand[0].x <= r && 1 <= cand[0].y && cand[0].y <= c) {
        int now = ask(cand[0]);
        if (now == 0) {
            printf("! %d %d %d %d\n", cand[0].x, cand[0].y, cand[2].x,
                   cand[2].y);
            valid = true;
        }
    }
    if (!valid)
        printf("! %d %d %d %d\n", cand[1].x, cand[1].y, cand[3].x, cand[3].y);
    fflush(stdout);

    return 0;
}