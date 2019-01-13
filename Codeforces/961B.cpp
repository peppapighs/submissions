#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n,k;
    scanf("%d%d",&n,&k);
    int a[n];
    for(int i=0;i<n;i++) {
        scanf("%d",&a[i]);
    }
    int res = 0;
    for(int i=0;i<n;i++) {
        int t;
        scanf("%d",&t);
        if(t) {
            res += a[i];
            a[i] = 0;
        }
    }

    for(int i=1;i<n;i++) {
        a[i] += a[i-1];
    }
    int maxi = a[k-1];
    for(int i=k;i<n;i++) {
        maxi = max(maxi,a[i]-a[i-k]);
    }

    printf("%d",res+maxi);

    return 0;
}
