#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    scanf("%d",&n);
    string s;
    cin >> s;
    int res = 0;
    for(int i=0;i<s.length();i++) {
        res++;
        if(i!=s.length()-1&&s[i]!=s[i+1]) {
            i++;
        }
    }

    printf("%d",res);

    return 0;
}
