#include <bits/stdc++.h>

using namespace std;

int main()
{
    long long m = 1000000007;
    long long l = 100001;

    long long t , k;
    scanf("%lld %lld",&t,&k);

    long long arr[l];

    for(int i=0;i<k;i++) {
        arr[i] = 1;
    }
    arr[0]=1;

    for(long i=1;i<l;i++) {
        arr[i] = arr[i-1];
        if(i-k>=0) {
            arr[i] +=arr[i-k];
        }
        arr[i]%=m;
    }

    long long qsum[l];
    qsum[0] = arr[0];
    for(int i=1;i<l;i++) {
        qsum[i] = qsum[i-1] + arr[i];
    }

    for(int i=0;i<t;i++) {
        long long a, b;
        scanf("%lld %lld",&a,&b);

        printf("%lld\n",(qsum[b] - qsum[a-1])%m);
    }

    return 0;
}
