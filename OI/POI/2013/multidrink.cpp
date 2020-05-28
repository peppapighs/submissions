#include <bits/stdc++.h>

using namespace std;

const int N = 5e5+5;

void brak() { printf("BRAK\n"); exit(0); }

int n;
int par[N], is_path[N], type[N], deg[N];
vector<int> g[N], path, ans;

void dfs(int u, int p) {
    par[u] = p;
    for(int v : g[u]) if(v != p)
        dfs(v, u);
}

int find_1(int u, int p) {
    int cnt = 0;
    for(int v : g[u]) if(v != par[u] && !is_path[v] && deg[v] > 1) {
        if(!find_1(v, u)) return 0;
        if(++cnt == 2) return 0;
    }
    return 1;
}

int find_2(int u, int p) {
    vector<int> relevant;
    for(int v : g[u]) if(v != par[u] && !is_path[v] && deg[v] > 1)
        relevant.emplace_back(v);
    if(relevant.size() > 2) return 0;
    if(relevant.empty()) return 1;
    if(relevant.size() == 1) return find_1(relevant[0], u);
    int a = relevant[0], b = relevant[1];
    return find_1(a, u) && find_1(b, u);
}

void print_2(int u, int p);

void print_1(int u, int p) {
    ans.emplace_back(u);
    for(int v : g[u]) if(v != par[u] && !is_path[v] && deg[v] > 1)
        print_2(v, u);
    for(int v : g[u]) if(v != par[u] && !is_path[v] && deg[v] == 1)
        ans.emplace_back(v);
}

void print_2(int u, int p) {
    for(int v : g[u]) if(v != par[u] && !is_path[v] && deg[v] == 1)
        ans.emplace_back(v);
    for(int v : g[u]) if(v != par[u] && !is_path[v] && deg[v] > 1)
        print_1(v, u);
    ans.emplace_back(u);
}

void print_3(int u, int p) {
    vector<int> relevant;
    for(int v : g[u]) if(v != par[u] && !is_path[v] && deg[v] == 1)
        ans.emplace_back(v);
    for(int v : g[u]) if(v != par[u] && !is_path[v] && deg[v] > 1)
        relevant.emplace_back(v);
    if(relevant.empty()) return void(ans.emplace_back(u));
    if(relevant.size() == 1) {
        ans.emplace_back(u);
        print_1(relevant[0], u);
    }
    int a = relevant[0], b = relevant[1];
    print_1(a, u), ans.emplace_back(u), print_2(b, u);
}

int main() {
    scanf("%d", &n);
    for(int i = 1, a, b; i < n; i++) {
        scanf("%d %d", &a, &b);
        g[a].emplace_back(b), g[b].emplace_back(a);
        ++deg[a], ++deg[b];
    }
    dfs(1, 0);

    path.emplace_back(n), is_path[n] = 1;
    while(path.back() != 1) {
        path.emplace_back(par[path.back()]);
        is_path[path.back()] = 1;
    }
    reverse(path.begin(), path.end());
    for(int i = 0; i < path.size(); i++) {
        if(i == 0) {
            if(g[path[i]].size() == 1) type[i] = 0;
            else if(find_1(path[i], 0)) type[i] = 1;
            else brak();
        } else {
            if(g[path[i]].size() == (i == path.size() - 1 ? 1 : 2)) type[i] = 0;
            else if((type[i-1] == 0 || type[i-1] == 2) && find_1(path[i], 0)) type[i] = 2;
            else if((type[i-1] == 0 || type[i-1] == 2) && find_2(path[i], 0)) type[i] = 3;
            else if(find_1(path[i], 0)) type[i] = 1;
            else brak();
        }
    }
    if(type[path.size() - 1] == 1 || type[path.size() - 1] == 3) brak();

    for(int i = 0; i < path.size(); i++) {
        if(type[i] == 0) ans.emplace_back(path[i]);
        else if(type[i] == 1) print_1(path[i], 0);
        else if(type[i] == 2) print_2(path[i], 0);
        else print_3(path[i], 0);
    }

    for(int x : ans) printf("%d\n", x);    

    return 0;
}