#include <bits/stdc++.h>

using namespace std;

int main()
{
    int m,o;
    scanf("%d%d",&m,&o);
    int arr[o];
    int sum = 0;
    for(int i=0;i<o;i++) {
        scanf("%d",&arr[i]);
        sum+=arr[i];
    }

    int low=0,high=sum;
    int res=sum;
    while(low<=high) {
        int mid = (low+high)/2;
        int csum = 0;
        int group = 1;
        for(int i=0;i<o;i++) {
            if(arr[i]>mid) {
                group = INT_MAX;
                break;
            }
            csum+=arr[i];
            if(csum>mid) {
                csum=arr[i];
                group++;
            }
        }
        if(group<=m) {
            high = mid-1;
            res = mid;
        } else {
            low = mid+1;
        }
    }

    printf("%d",res);

    return 0;
}
