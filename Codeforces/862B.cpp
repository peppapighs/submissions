#include <bits/stdc++.h>

using namespace std;

long long l=0,r=0;

void dfs(vector<int> adj[],bool *inset,int n,int isl) {
    if(isl) {
        l++;
    } else {
        r++;
    }
    inset[n] = true;
    for(int i=0;i<adj[n].size();i++) {
        if(!inset[adj[n][i]]) {
            dfs(adj,inset,adj[n][i],1-isl);
        }
    }
}

int main()
{
    long long n;
    scanf("%lld",&n);
    vector<int> adj[n];
    bool inset[n] = {false};

    for(int i=0;i<n-1;i++) {
        int u,v;
        scanf("%d%d",&u,&v);
        u--;
        v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(adj,inset,0,1);

    printf("%lld",(l*r)-(n-1));

    return 0;
}
