#include <bits/stdc++.h>

using namespace std;

bool *visit;
vector<int> st;
long long n;
int x,y;

void dfs(vector<int> g[],int u,int p) {
    st.push_back(u);
    if(u==y) {
        for(int i=0;i<st.size();i++) {
            visit[st[i]] = true;
        }
    } else {
        for(int v : g[u]) {
            if(v!=p) {
                dfs(g,v,u);
            }
        }
    }
    st.pop_back();
}

long long dp(vector<int> g[],int u,int p) {
    long long ans = 0;
    for(int v : g[u]) {
        if(v!=p&&!visit[v]) {
            ans+=dp(g,v,u);
        }
    }
    return ans+1;
}

int main()
{
    scanf("%lld%d%d",&n,&x,&y);
    if(n==1) {
        printf("0");
        return 0;
    }
    x--;
    y--;
    vector<int> g[n];
    for(int i=0;i<n-1;i++) {
        int u,v;
        scanf("%d%d",&u,&v);
        g[--u].push_back(--v);
        g[v].push_back(u);
    }

    visit = new bool[n] {false};

    dfs(g,x,-1);
    long long a = dp(g,x,-1);
    long long b = dp(g,y,-1);
    printf("%lld",(n*(n-1))-(a*b));

    return 0;
}
