#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    long long dorm[n],let[m];
    long long pre[n];
    for(int i=0;i<n;i++) {
        scanf("%lld",&dorm[i]);
    }
    for(int i=0;i<m;i++) {
        scanf("%lld",&let[i]);
    }
    pre[0] = dorm[0];
    for(int i=1;i<n;i++) {
        pre[i]=pre[i-1]+dorm[i];
    }
    for(int i=0;i<m;i++) {
        int low = 0,high=n-1;
        int res=0;
        while(low<=high) {
            int mid=(low+high)/2;
            if(let[i]<=pre[mid]) {
                res=mid;
                high=mid-1;
            } else {

                low=mid+1;
            }
        }
        long long ans;
        if(res>0) {
            ans=let[i]-pre[res-1];
        } else {
            ans=let[i];
        }
        printf("%d %lld\n",res+1,ans);
    }

    return 0;
}
