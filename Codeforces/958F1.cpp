#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    int col[m] = {0};
    int arr[n];

    for(int i=0;i<n;i++) {
        scanf("%d",&arr[i]);
        col[arr[i]-1]++;
    }

    bool ans = true;
    for(int i=0;i<m;i++) {
        int k;
        scanf("%d",&k);
        if(k>col[i]) {
            ans = false;
        }
    }

    if(ans) {
        printf("YES");
    } else {
        printf("NO");
    }

    return 0;
}
