#include <bits/stdc++.h>

using namespace std;

int n,a,b;

bool check(int x) {
    if(a<x||b<x) {
        return false;
    }
    return ((a/x)+(b/x))>=n;
}

int main()
{
    scanf("%d%d%d",&n,&a,&b);

    int low = 1,high=a+b;
    int res;
    while(low<=high) {
        int mid = (low+high)/2;
        if(check(mid)) {
            res = mid;
            low = mid+1;
        } else {
            high = mid-1;
        }
    }

    printf("%d",res);

    return 0;
}
