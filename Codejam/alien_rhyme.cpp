#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e3 + 5;

int n, ptr;
int t[N * N][26], par[N * N];
pii cnt[N * N];

priority_queue<pii> Q;

void solve(int idx) {
    int ans = 0;
    memset(t, 0, sizeof t), memset(par, 0, sizeof par);
    ptr = 0;
    fill_n(cnt, N * N, pii(0, 0));
    Q = priority_queue<pii>();
    cin >> n;
    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        for (int i = s.length() - 1, d = 1, cur = 0; ~i; i--, d++) {
            int &now = t[cur][s[i] - 'A'];
            if (!now)
                now = ++ptr, par[ptr] = cur;
            cnt[now].x = d, ++cnt[now].y;
            cur = now;
        }
    }
    for (int i = 1; i <= ptr; i++)
        if (cnt[i].y >= 2)
            Q.emplace(cnt[i].x, i);
    while (!Q.empty()) {
        int now = Q.top().y;
        Q.pop();
        if (cnt[now].y < 2)
            continue;
        ans += 2;
        cnt[now].y = 0;
        now = par[now];
        while (now) {
            cnt[now].y -= 2;
            if (cnt[now].y == 2)
                Q.emplace(cnt[now].x, now);
            now = par[now];
        }
    }
    cout << "Case #" << idx << ": " << ans << "\n";
}

int T;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> T;
    for (int i = 1; i <= T; i++)
        solve(i);

    return 0;
}