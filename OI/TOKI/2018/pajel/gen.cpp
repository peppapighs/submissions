#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 505;
const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};

int n, p, cc, scc;
int a[N][N], g[N][N], par[N * N], spar[N * N];

int f(int r, int c) { return (r - 1) * n + c; }

int find(int x) { return par[x] = x == par[x] ? x : find(par[x]); }

void add(int r, int c, int col) {
    if (a[r][c])
        return;
    ++cc, a[r][c] = col;
    for (int i = 0; i < 4; i++) {
        int nr = r + dx[i], nc = c + dy[i];
        if (nr < 1 || nr > n || nc < 1 || nc > n)
            continue;
        if (a[nr][nc] == a[r][c] && find(f(nr, nc)) != find(f(r, c))) {
            --cc;
            par[find(f(nr, nc))] = find(f(r, c));
        }
    }
}

void answer(int a[N][N]) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (a[i][j] == 1)
                printf("M");
            else if (a[i][j] == 2)
                printf("B");
            else
                printf("-");
        }
        printf("\n");
    }
    exit(0);
}

void print(int a[N][N]) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (a[i][j] == 1)
                cerr << "M";
            else if (a[i][j] == 2)
                cerr << "B";
            else
                cerr << "-";
        }
        cerr << "\n";
    }
}

default_random_engine dre(time(NULL));
uniform_int_distribution<int> uid(1, 1e9);

int main() {
    iota(par, par + (N * N), 0);

    scanf("%d %d", &n, &p);
    for (int i = 1; i <= n; i++) {
        char S[100];
        scanf(" %s", S + 1);
        if (S[1] == '0')
            for (int j = 1; j <= n; j++)
                a[j][i] = -1;
        else if (S[1] != '-') {
            int now = strlen(S + 1), val = 0;
            for (int j = 1; j < now; j++)
                val = val * 10 + (S[j] - '0');
            for (int j = 1; j < val; j++)
                a[j][i] = -1;
            add(val, i, S[now] == 'M' ? 1 : 2);
        }
    }
    for (int i = 1; i <= n; i++) {
        char S[100];
        scanf(" %s", S + 1);
        if (S[1] == '0')
            for (int j = 1; j <= n; j++)
                a[i][j] = -1;
        else if (S[1] != '-') {
            int now = strlen(S + 1), val = 0;
            for (int j = 1; j < now; j++)
                val = val * 10 + (S[j] - '0');
            for (int j = 1; j < val; j++)
                a[i][j] = -1;
            add(i, val, S[now] == 'M' ? 1 : 2);
        }
        scanf(" %s", S + 1);
        if (S[1] == '0')
            for (int j = 1; j <= n; j++)
                a[i][j] = -1;
        else if (S[1] != '-') {
            int now = strlen(S + 1), val = 0;
            for (int j = 1; j < now; j++)
                val = val * 10 + (S[j] - '0');
            for (int j = 1; j < val; j++)
                a[i][n - j + 1] = -1;
            add(i, n - val + 1, S[now] == 'M' ? 1 : 2);
        }
    }
    for (int i = 1; i <= n; i++) {
        char S[100];
        scanf(" %s", S + 1);
        if (S[1] == '0')
            for (int j = 1; j <= n; j++)
                a[j][i] = -1;
        else if (S[1] != '-') {
            int now = strlen(S + 1), val = 0;
            for (int j = 1; j < now; j++)
                val = val * 10 + (S[j] - '0');
            for (int j = 1; j < val; j++)
                a[n - j + 1][i] = -1;
            add(n - val + 1, i, S[now] == 'M' ? 1 : 2);
        }
    }
    for (int i = 1; i <= n * n; i++)
        spar[i] = par[i];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            g[i][j] = a[i][j];
    scc = cc;
    while (1) {
        if (cc <= p)
            answer(a);
        vector<pii> M, B;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (par[f(i, j)] == f(i, j)) {
                    if (a[i][j] == 1)
                        M.emplace_back(i, j);
                    else if (a[i][j] == 2)
                        B.emplace_back(i, j);
                }
        int mmx = cc;
        pii ma, mb;
        shuffle(M.begin(), M.end(), dre);
        shuffle(B.begin(), B.end(), dre);
        if (uid(dre) % 2)
            swap(M, B);

        int tmp[N][N], tpar[N * N], tcc = cc;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                tmp[i][j] = a[i][j];
        for (int i = 1; i <= n * n; i++)
            tpar[i] = par[i];
        for (int i = 0; i < M.size(); i++)
            for (int j = i + 1; j < M.size(); j++) {
                pii st = M[i], en = M[j];
                vector<vector<int>> d(N, vector<int>(N, 1e9));
                vector<vector<pii>> par(N, vector<pii>(N, pii(0, 0)));
                queue<pii> Q;
                d[st.x][st.y] = 0;
                Q.emplace(st.x, st.y);
                while (!Q.empty()) {
                    pii now = Q.front();
                    Q.pop();
                    for (int i = 0; i < 4; i++) {
                        int nr = now.x + dx[i], nc = now.y + dy[i];
                        if (nr < 1 || nr > n || nc < 1 || nc > n)
                            continue;
                        if ((a[nr][nc] == 0 || a[nr][nc] == a[st.x][st.y]) &&
                            d[now.x][now.y] + 1 < d[nr][nc]) {
                            d[nr][nc] = d[now.x][now.y] + 1;
                            par[nr][nc] = pii(now.x, now.y);
                            Q.emplace(nr, nc);
                        }
                    }
                }
                if (d[en.x][en.y] != 1e9) {
                    pii now = par[en.x][en.y];
                    while (now != st) {
                        add(now.x, now.y, a[st.x][st.y]);
                        now = par[now.x][now.y];
                    }
                    if (cc < mmx) {
                        mmx = cc;
                        ma = st, mb = en;
                    }
                }
                // print(a);
                for (int i = 1; i <= n * n; i++)
                    ::par[i] = tpar[i];
                for (int i = 1; i <= n; i++)
                    for (int j = 1; j <= n; j++)
                        a[i][j] = tmp[i][j];
                cc = tcc;
            }
        if (mmx == cc) {
            for (int i = 1; i <= n * n; i++)
                ::par[i] = spar[i];
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    a[i][j] = g[i][j];
            cc = scc;
        } else {
            pii st = ma, en = mb;
            vector<vector<int>> d(N, vector<int>(N, 1e9));
            vector<vector<pii>> par(N, vector<pii>(N, pii(0, 0)));
            queue<pii> Q;
            d[st.x][st.y] = 0;
            Q.emplace(st.x, st.y);
            while (!Q.empty()) {
                pii now = Q.front();
                Q.pop();
                for (int i = 0; i < 4; i++) {
                    int nr = now.x + dx[i], nc = now.y + dy[i];
                    if (nr < 1 || nr > n || nc < 1 || nc > n)
                        continue;
                    if ((a[nr][nc] == 0 || a[nr][nc] == a[st.x][st.y]) &&
                        d[now.x][now.y] + 1 < d[nr][nc]) {
                        d[nr][nc] = d[now.x][now.y] + 1;
                        par[nr][nc] = pii(now.x, now.y);
                        Q.emplace(nr, nc);
                    }
                }
            }
            pii now = en;
            while (now != st) {
                add(now.x, now.y, a[st.x][st.y]);
                now = par[now.x][now.y];
            }
        }
        cerr << "===========================\n";
        cerr << "connected component = " << cc << "\n";
    }

    return 0;
}