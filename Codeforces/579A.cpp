#include <bits/stdc++.h>

using namespace std;

int main()
{
    int x;
    scanf("%d",&x);

    int ans = 0;

    while(x>0) {
        ans += (x&1);
        x = x >> 1;
    }

    printf("%d",ans);

    return 0;
}
