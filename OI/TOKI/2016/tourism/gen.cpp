#include <bits/stdc++.h>

using namespace std;

char sub[100];

int n, m, l;
int g[15][15];
default_random_engine ran(time(NULL));
uniform_int_distribution<int> uid(1, 1e9);

int check() {
    set<int> s;
    vector<int> v;
    for(int i = 2; i <= n; i++) v.emplace_back(i);
    do {
        int sum = g[1][v[0]] + g[v.back()][1];
        for(int i = 1; i < v.size(); i++) sum += g[v[i]][v[i-1]];
        s.emplace(sum);
    } while(next_permutation(v.begin(), v.end()));
    return s.size();
}

void answer() {
    printf("========= Optimization ========\n");
    l /= 2;
    int cnt = 0;
    for(int i = 1; i <= n; i++) for(int j = i + 1; j <= n; j++) if(g[i][j] > l) ++cnt;
    for(int i = 1; i <= n; i++) for(int j = i + 1; j <= n; j++) if(g[i][j] > l) {
        int now;
        set<int> asked;
        while(1) {
            if(asked.size() == l) {
                printf("========== Unable to Optimize ==========\n");
                exit(0);
            }

            int cur = uid(ran) % l + 1;
            if(asked.find(cur) != asked.end()) continue;
            asked.emplace(cur), g[i][j] = g[j][i] = cur;
            now = check();
            if(now >= m) break;
        }
        printf("edges left = %d, optimizing....\n", --cnt);
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) printf("%d ", g[i][j]);
            printf("\n");
        }
        printf("\n");
    }
    printf("========== Answer ===========\n");
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) printf("%d ", g[i][j]);
        printf("\n");
    }
    exit(0);
}

int main() {
    scanf("%s", sub);
    scanf("%d %d %d", &n, &m, &l);

    l *= 2;

    printf("========= Hill Climbing : %d ==========\n", l);

    bool valid = false;
    while(1) {
        if(!valid) for(int i = 1; i <= n; i++) for(int j = i + 1; j <= n; j++)
            g[i][j] = g[j][i] = uid(ran) % l + 1;
        int now = check(), r = 1, c = 1, k = g[1][1];
        if(now >= m) answer();
        int o[15][15];
        for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) o[i][j] = g[i][j];
        valid = false;
        for(int i = 1; i <= n; i++) for(int j = i + 1; j <= n; j++) {
            g[i][j] = g[j][i] = uid(ran) % l + 1;
            int ret = check();
            if(ret >= m) answer();
            if(ret > now) {
                now = ret, valid = true;
                r = i, c = j;
                k = g[i][j];
            } 
            g[i][j] = g[j][i] = o[i][j];
        }
        g[r][c] = g[c][r] = k;
        printf("current best = %d\n", now);
    }

    return 0;
}