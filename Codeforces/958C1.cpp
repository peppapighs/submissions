#include <bits/stdc++.h>

using namespace std;

int main()
{
    long long n,p;
    scanf("%lld%lld",&n,&p);
    long long arr[n];
    for(int i=0;i<n;i++) {
        scanf("%lld",&arr[i]);
        if(i>0) {
            arr[i]+=arr[i-1];
        }
    }
    long long res = -1;
    for(int i=0;i<n-1;i++) {
        res = max(res,(arr[i]%p)+((arr[n-1]-arr[i])%p));
    }

    printf("%lld",res);

    return 0;
}
