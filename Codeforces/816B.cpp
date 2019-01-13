#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n,k,q;
    scanf("%d%d%d",&n,&k,&q);
    int c[200001] = {0},g[200001] = {0};
    for(int i=0;i<n;i++) {
        int l,r;
        scanf("%d%d",&l,&r);
        c[l]++;
        c[r+1]--;
    }
    for(int i=1;i<200001;i++) {
        c[i]+=c[i-1];
        if(c[i]>=k) {
            g[i] = 1;
        }
    }
    for(int i=1;i<200001;i++) {
        g[i]+=g[i-1];
    }

    for(int i=0;i<q;i++) {
        int l,r;
        scanf("%d%d",&l,&r);
        printf("%d\n",g[r]-g[l-1]);
    }

    return 0;
}
