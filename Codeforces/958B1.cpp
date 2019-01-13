#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    scanf("%d",&n);
    vector<int> g[n];

    for(int i=0;i<n-1;i++) {
        int u,v;
        scanf("%d%d",&u,&v);
        g[u-1].push_back(v-1);
        g[v-1].push_back(u-1);
    }
    int res = 0;
    for(int i=0;i<n;i++) {
        if(g[i].size()==1) {
            res++;
        }
    }

    printf("%d",res);

    return 0;
}
