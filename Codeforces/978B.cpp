#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    string s;
    scanf("%d",&n);
    cin >> s;
    int cnt=0;
    int ans=0;
    for(int i=0;i<n;i++) {
        if(s[i]=='x') {
            cnt++;
        } else {
            ans+=max(0,cnt-2);
            cnt = 0;
        }
    }
    ans+=max(0,cnt-2);
    printf("%d",ans);

    return 0;
}
