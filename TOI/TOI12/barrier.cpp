#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n,w;
    int ans=0,siz=0;
    scanf("%d%d",&n,&w);
    int arr[n+w-1] = {0};
    for(int i=0;i<n;i++) {
        scanf("%d",&arr[i]);
    }
    for(int i=1;i<n;i++) {
        arr[i]+=arr[i-1];
    }

    for(int i=0;i<n+w-1;i++) {
        printf("%d ",arr[i]);
    }

    printf("\n");

    deque<int> win;
    for(int i=0;i<min(w,n);i++) {
        while(!win.empty()&&arr[i]>=arr[win.back()]) {
            win.pop_back();
        }
        win.push_back(i);
    }
    for(int i=w;i<n+w-1;i++) {
        int k=i-w-1>=0?arr[i-w-1]:0;
        if(arr[win.front()]-k>0&&arr[win.front()]-k>ans) {
            ans=arr[win.front()]-k;
            siz = win.front()-i+w+1;
        } else if(arr[win.front()]-k>0&&arr[win.front()]-k==ans&&win.front()-i+w+1<siz) {
            siz=win.front()-i+w+1;
        }
        printf("%d ",arr[win.front()]);
        while(!win.empty()&&win.front()<=i-w) {
            win.pop_front();
        }
        while(!win.empty()&&arr[i]>=arr[win.back()]) {
            win.pop_back();
        }
        win.push_back(i);
    }
    int k=arr[n-2];
    if(arr[win.front()]-k>0&&arr[win.front()]-k>ans) {
        ans=arr[win.front()]-k;
        siz = 1;
    } else if(arr[win.front()]-k>0&&arr[win.front()]-k==ans&&1<siz) {
        siz=1;
    }

    printf("%d\n%d",ans,siz);


    return 0;
}
