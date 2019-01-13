#include <bits/stdc++.h>

using namespace std;

int main()
{
    int k;
    string s;
    scanf("%d ",&k);
    getline(cin,s);

    int low = 0, high = s.length()-1;
    int res=s.length();
    while(low<=high) {
        int mid = (low+high)/2;
        int pos = 0;
        int prev = -1;
        int l = 0;
        for(int i=0;i<s.length();i++) {
            pos++;
            if(pos>mid) {
                if(prev!=-1) {
                    l++;
                    pos = i-prev;
                    prev = -1;
                }else{
                    l = INT_MAX;
                    break;
                }
            }
            if(s[i]==' '||s[i]=='-') {
                prev = i;
            }
            if(i==s.length()-1) {
                l++;
            }
        }

        if(l>k) {
            low = mid+1;
        } else {
            high = mid-1;
            res = mid;
        }
    }

    printf("%d",res);

    return 0;
}
