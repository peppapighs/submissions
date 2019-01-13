#include <bits/stdc++.h>

using namespace std;

map<double,int> coord;
vector<double> x;

int main()
{
    int n;
    scanf("%d",&n);
    while(n--) {
        string s;
        cin >> s;
        int i = 1;
        double a=0,b=0,c=0;
        while(s[i]!='+') {
            a = (a*10) + (s[i]-'0');
            i++;
        }
        i++;
        while(s[i]!=')') {
            b = (b*10) + (s[i]-'0');
            i++;
        }
        i+=2;
        while(i<s.length()) {
            c = (c*10) + (s[i]-'0');
            i++;
        }
        coord[(a+b)/c]++;
        x.push_back((a+b)/c);
        //printf("%lf %lf %lf\n",a,b,c);
    }
    for(int i=0;i<x.size();i++) {
        printf("%d ",coord[x[i]]);
    }

    return 0;
}
