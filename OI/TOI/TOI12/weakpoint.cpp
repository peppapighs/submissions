#include <bits/stdc++.h>

using namespace std;

bool visit[500000];
int dp[500000];
bool inst[500000];
bool inCycle = false;
vector<int> cycle;
int n, m;
vector<int> st;

// Detecting Cycle
void dfs1(vector<int> g[], int n, int p) {
    visit[n] = true;
    inst[n] = true;
    st.push_back(n);
    for (int i = 0; i < g[n].size(); i++) {
        int v = g[n][i];
        if (v != p) {
            if (!visit[v]) {
                dfs1(g, v, n);
            } else if (inst[v]) {
                for (int j = st.size() - 1; j >= 0; j--) {
                    if (st[j] == v) {
                        break;
                    }
                    cycle.push_back(st[j]);
                    if (st[j] == m) {
                        inCycle = true;
                    }
                }
                cycle.push_back(v);
                if (v == m) {
                    inCycle = true;
                }
            }
        }
    }
    inst[n] = false;
    st.pop_back();
}

// Find number of node in the component
void dfs2(vector<int> g[], int v, int &cnt) {
    cnt++;
    visit[v] = true;
    for (int i = 0; i < g[v].size(); i++) {
        if (!visit[g[v][i]]) {
            dfs2(g, g[v][i], cnt);
        }
    }
}

// DP to find how many children of each node
void dfs3(vector<int> g[], int v) {
    visit[v] = true;
    for (int i = 0; i < g[v].size(); i++) {
        if (!visit[g[v][i]]) {
            dfs3(g, g[v][i]);
            dp[v] += (dp[g[v][i]] + 1);
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    m--;
    vector<int> g[n];

    for (int i = 0; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u - 1].push_back(v - 1);
        g[v - 1].push_back(u - 1);
    }
    dfs1(g, 0, 0);
    memset(visit, false, sizeof visit);
    if (inCycle) {
        for (int i = 0; i < cycle.size(); i++) {
            visit[cycle[i]] = true;
        }
        for (int i = 0; i < cycle.size(); i++) {
            dfs3(g, cycle[i]);
        }
        int resn;
        int resmax = -1;
        for (int i = 0; i < n; i++) {
            if (i != m) {
                if (dp[i] > resmax) {
                    resmax = dp[i];
                    resn = i;
                } else if (dp[i] == resmax && i < resn) {
                    resn = i;
                }
            }
        }
        printf("%d\n%d", resn + 1, resmax);
    } else {
        visit[m] = true;
        int resn;
        int resmax = -1;
        for (int i = 0; i < g[m].size(); i++) {
            int v = g[m][i];
            int cnt = 0;
            dfs2(g, v, cnt);
            if (cnt > resmax) {
                resn = v;
                resmax = cnt;
            } else if (cnt == resmax && v < resn) {
                resn = v;
            }
        }

        printf("%d\n%d", resn + 1, resmax - 1);
    }

    return 0;
}
