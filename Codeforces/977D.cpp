#include <bits/stdc++.h>

using namespace std;

int n;
long long arr[100];
vector<int> st;
bool gg = false;

void dfs(vector<int> g[],int u,int p) {
    if(!gg) {
        st.push_back(u);
        if(st.size()==n) {
            for(int i=0;i<n;i++) {
                printf("%lld ",arr[st[i]]);
            }
            gg = true;
        } else {
            for(int i=0;i<g[u].size();i++) {
                int v =g[u][i];
                if(v!=p) {
                    dfs(g,v,u);
                }
            }
        }
        st.pop_back();
    }
}

int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++) {
        scanf("%lld",&arr[i]);
    }
    vector<int> g[n];
    for(int i=0;i<n;i++) {
        for(int j=i+1;j<n;j++) {
            if(arr[i]*2==arr[j]) {
                g[i].push_back(j);
            } else if(arr[i]*3==arr[j]) {
                g[j].push_back(i);
            } else if(arr[i]%3==0&&arr[i]/3==arr[j]) {
                g[i].push_back(j);
            } else if(arr[i]/2==arr[j]) {
                g[j].push_back(i);
            }
        }
    }
    /*for(int i=0;i<n;i++) {
        printf("%d - ",i);
        for(int j=0;j<g[i].size();j++) {
            printf("%d ",g[i][j]);
        }
        printf("\n");
    }*/
    for(int i=0;i<n;i++) {
        dfs(g,i,-1);
        if(gg) {
            return 0;
        }
    }

    return 0;
}
