#include <bits/stdc++.h>

using namespace std;

int main()
{
    long long n,m;
    scanf("%lld%lld",&n,&m);

    if(n<=m) {
        printf("%lld",n);
        return 0;
    }
    n-=m;
    long long low = 0,high = 2e9;
    long long res;
    while(low<=high) {
        long long mid = (low+high)/2;
        if((mid*(mid+1)/2)>=n) {
            res = mid;
            high = mid-1;
        } else {
            low = mid+1;
        }
    }

    printf("%lld",m+res);

    return 0;
}
