#include <bits/stdc++.h>

using namespace std;

vector<int> pack,aste;

bool check(int time) {
    int can = 0;
    for(int j=0;j<pack.size();j++) {
        int left=pack[j],right=pack[j];
        for(can;can<aste.size();can++) {
            left = min(left,aste[can]);
            right = max(right,aste[can]);
            if(right-left+min(right-pack[j],pack[j]-left)>time) {
                break;
            }
        }
    }
    return can == aste.size();
}

int main()
{
    int n;
    string s;
    scanf("%d",&n);
    cin >> s;
    for(int i=0;i<s.length();i++) {
        if(s[i]=='*') {
            aste.push_back(i);
        } else if(s[i]=='P') {
            pack.push_back(i);
        }
    }

    int low = 0,high = n*2;
    int res = n*2;
    while(low<=high) {
        int mid = (low+high)/2;
        if(check(mid)) {
            high = mid-1;
            res = mid;
        } else {
            low = mid+1;
        }
    }

    printf("%d",res);

    return 0;
}
