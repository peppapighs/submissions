#include <bits/stdc++.h>

using namespace std;

int main()
{
    int q;
    scanf("%d",&q);
    while(q--) {
        int n;
        string s;
        scanf("%d",&n);
        cin >> s;
        map<string,int> sub;
        for(int i=0;i<s.length()-n+1;i++) {
            string z = s.substr(i,n);
            if(sub.find(z)==sub.end()) {
                sub[z] = 1;
            } else {
                sub[z]++;
            }
        }
        int res = 0;
        string ans = "";
        for(map<string,int>::iterator it=sub.begin();it!=sub.end();it++) {
            if(it->second>res) {
                res=it->second;
                ans=it->first;
            }
        }
        cout << ans;
    }

    return 0;
}
