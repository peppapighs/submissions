#include <bits/stdc++.h>

using namespace std;

map<string,int> m;

int main()
{
    int n;
    scanf("%d",&n);
    string s;
    cin >> s;
    for(int i=0;i<n-1;i++) {
        m[s.substr(i,2)]++;
    }
    string ans;
    int mx = 0;
    for(map<string,int>::iterator it=m.begin();it!=m.end();it++) {
        if(it->second>mx) {
            mx=it->second;
            ans = it->first;
        }
    }

    cout << ans;

    return 0;
}
