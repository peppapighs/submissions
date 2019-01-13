#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n,u;
    scanf("%d%d",&n,&u);
    double arr[n];
    for(int i=0;i<n;i++) {
        scanf("%lf",&arr[i]);
    }

    double res = -1;

    for(int i=0;i<n-2;i++) {
        int low = i+2,high = n-1;
        double ek = -1;
        while(low<=high) {
            int mid = (low+high)/2;
            if(arr[mid]-arr[i]<=u) {
                ek = arr[mid];
                low = mid+1;
            } else {
                high = mid-1;
            }
        }

        if(ek!=-1) {
            res = max(res,(ek-arr[i+1])/(ek-arr[i]));
        }
    }

    printf("%.10lf",res);

    return 0;
}
