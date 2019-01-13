#include <bits/stdc++.h>

using namespace std;

int main()
{
    long long n;
    scanf("%lld",&n);
    if(n==0) {
        printf("0");
        return 0;
    }
    if(n%2==0) {
        printf("%lld",n+1);
    } else {
        printf("%lld",(n+1)/2);
    }

    return 0;
}
