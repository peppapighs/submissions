#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    scanf("%d",&n);
    string s;
    cin >> s;
    int res = n;
    for(int i=1;i<=n/2;i++) {
        bool k = true;
        for(int j=0;j<i;j++) {
            if(s[j]!=s[j+i]) {
                k=false;
            }
        }
        if(k) {
            res = min(n,n-i+1);
        }
    }

    printf("%d",res);

    return 0;
}
