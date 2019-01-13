#include <bits/stdc++.h>

using namespace std;

int nd,md=0;

void dfs(vector<int> g[],int n,int p,int d) {
    if(d>=md) {
        nd = n;
        md = d;
    }
    for(int i=0;i<g[n].size();i++) {
        if(g[n][i]!=p) {
            dfs(g,g[n][i],n,d+1);
        }
    }
}

void dfs2(vector<int> g[],int *dep,int *freq,int n,int p) {
    for(int i=0;i<g[n].size();i++) {
        if(g[n][i]!=p) {
            dfs2(g,dep,freq,g[n][i],n);
            dep[n] = max(dep[n],dep[g[n][i]]+1);
        }
    }
    freq[dep[n]]++;
}

int main()
{
    int n;
    scanf("%d",&n);
    vector<int> g[n];
    int dep[n] = {0};
    int freq[n] = {0};
    for(int i=0;i<n-1;i++) {
        int u,v;
        scanf("%d%d",&u,&v);
        g[u-1].push_back(v-1);
        g[v-1].push_back(u-1);
    }
    dfs(g,0,-1,0);
    md = 0;
    dfs(g,nd,-1,0);
    dfs2(g,dep,freq,nd,-1);

    return 0;
}
