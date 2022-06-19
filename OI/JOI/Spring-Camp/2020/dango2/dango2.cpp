#include <bits/stdc++.h>

#define iii tuple<int, int, int>

using namespace std;

mt19937 seed(time(NULL));
int range(int l, int r) { return uniform_int_distribution<int>(l, r)(seed); }

const int N = 505;
const int M = 1e6 + 5;

int R, C, dango, limit;
int t[M], logn;

void update(int x, int k) {
    for (int i = x; i <= dango; i += i & -i)
        t[i] += k;
}

int get(int x) {
    int i = 0;
    for (int j = logn; ~j; j--)
        if ((i | (1 << j)) <= dango && t[i | (1 << j)] < x)
            x -= t[i |= (1 << j)];
    return i + 1;
}

char A[N][N], B[N][N];
vector<int> V[N][N], g[M];
iii pos[M];

int cnt, ans_cnt;
bitset<M> ans, chk;

const double delta = 0.99999994, initT = 1e3;

void simulated_annealing() {
    for (int i = 1; i <= dango; i++)
        update(i, 1);
    double T = initT;

    int timer = 0;
    while (T >= 1e-6) {
        if (ans_cnt >= limit || cnt == dango)
            break;
        for (int k = 1; k <= 5; k++) {
            if (ans_cnt >= limit || cnt == dango)
                break;
            int u = get(range(1, dango - cnt));

            int add = 1;
            for (int v : g[u])
                if (chk[v])
                    --add;
            int ncnt = cnt + add;

            // If new dango is better, always add it
            // If new dango makes answer worse, get the probability to add it
            bool valid = false;
            if (ncnt <= cnt) {
                double P = exp(add / (T / 10));
                double rnd = seed() / (double)(4294967296);
                valid = (rnd <= P);
            } else
                valid = true;
            if (valid) {
                chk[u] = 1, update(u, -1);
                for (int v : g[u])
                    if (chk[v])
                        chk[v] = 0, update(v, 1);
                cnt = ncnt;
                if (cnt > ans_cnt) {
                    ans_cnt = cnt;
                    ans = chk;
                }
            }
        }

        T *= delta;
        if (++timer >= 200000) {
            cerr << "Temp = " << T << " Ans = " << ans_cnt << " Cnt = " << cnt
                 << "\n";
            timer -= 200000;
        }
    }
    cerr << "ans = " << ans_cnt << "\n";
}

char str_in[100], str_out[100];

int main() {
    scanf("%d %s %s", &limit, str_in, str_out);
    freopen(str_in, "r", stdin);
    freopen(str_out, "w", stdout);

    scanf("%d %d", &R, &C);
    for (int i = 1; i <= R; i++)
        scanf(" %s", A[i] + 1);

    // Construct all valid dango
    auto valid = [&](char a, char b) {
        return (a == 'P' && b == 'G') || (a == 'G' && b == 'P');
    };
    for (int i = 1; i <= R; i++)
        for (int j = 1; j <= C; j++) {
            if (A[i][j] != 'W')
                continue;
            if (valid(A[i - 1][j], A[i + 1][j])) {
                V[i][j].emplace_back(++dango);
                V[i - 1][j].emplace_back(dango);
                V[i + 1][j].emplace_back(dango);
                pos[dango] = iii(i, j, 0);
            }
            if (valid(A[i][j - 1], A[i][j + 1])) {
                V[i][j].emplace_back(++dango);
                V[i][j - 1].emplace_back(dango);
                V[i][j + 1].emplace_back(dango);
                pos[dango] = iii(i, j, 1);
            }
            if (valid(A[i - 1][j - 1], A[i + 1][j + 1])) {
                V[i][j].emplace_back(++dango);
                V[i - 1][j - 1].emplace_back(dango);
                V[i + 1][j + 1].emplace_back(dango);
                pos[dango] = iii(i, j, 2);
            }
            if (valid(A[i + 1][j - 1], A[i - 1][j + 1])) {
                V[i][j].emplace_back(++dango);
                V[i + 1][j - 1].emplace_back(dango);
                V[i - 1][j + 1].emplace_back(dango);
                pos[dango] = iii(i, j, 3);
            }
        }

    cerr << "Finished constructing dango\n";
    cerr << "dango = " << dango << "\n";

    for (int i = 1; i <= R; i++)
        for (int j = 1; j <= C; j++)
            for (int x = 0; x < V[i][j].size(); x++)
                for (int y = 0; y < x; y++)
                    g[V[i][j][x]].emplace_back(V[i][j][y]),
                        g[V[i][j][y]].emplace_back(V[i][j][x]);

    cerr << "Finished constructing dango graph"
         << "\n";

    logn = 31 - __builtin_clz(dango);

    simulated_annealing();

    for (int i = 1; i <= R; i++)
        for (int j = 1; j <= C; j++)
            B[i][j] = A[i][j];

    for (int i = 1; i <= dango; i++)
        if (ans[i]) {
            int r, c, t;
            tie(r, c, t) = pos[i];
            if (t == 0)
                B[r][c] = '|';
            if (t == 1)
                B[r][c] = '-';
            if (t == 2)
                B[r][c] = '\\';
            if (t == 3)
                B[r][c] = '/';
        }

    for (int i = 1; i <= R; i++)
        printf("%s\n", B[i] + 1);

    return 0;
}