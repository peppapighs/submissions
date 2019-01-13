#include <bits/stdc++.h>

using namespace std;

void dfs(vector<int> graph[],bool *visit,int n,long long& node) {
    node++;
    visit[n] = true;
    for(int i=0;i<graph[n].size();i++) {
        if(!visit[graph[n][i]]) {
            dfs(graph,visit,graph[n][i],node);
        }
    }
}

int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    vector<int> graph[n];
    bool visit[n] = {false};
    for(int i=0;i<m;i++) {
        int u,v;
        scanf("%d%d",&u,&v);
        graph[u-1].push_back(v-1);
        graph[v-1].push_back(u-1);
    }

    long long res = 0;
    for(int i=0;i<n;i++) {
        long long node = 0;
        if(!visit[i]&&graph[i].size()) {
            dfs(graph,visit,i,node);
            res+=node*(node-1)/2;
        }
    }

    printf(res==m?"YES":"NO");

    return 0;
}
