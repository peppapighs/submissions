#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    scanf("%d",&n);
    pair<int,int> friends[n];
    for(int i=0;i<n;i++) {
        scanf("%d",&friends[i].first);
    }
    for(int i=0;i<n;i++) {
        scanf("%d",&friends[i].second);
    }

    sort(friends,friends+n);

    double low = 0,high=1e9;
    double res;
    for(int e=0;e<100;e++) {
        double mid = (low+high)/2;
        double minr=DBL_MAX,maxl=0;
        for(int i=0;i<n;i++) {
            minr = min(minr,friends[i].first+(mid*friends[i].second));
            maxl = max(maxl,friends[i].first-(mid*friends[i].second));
        }
        if(maxl<=minr) {
            high = mid;
            res = mid;
        } else {
            low = mid;
        }
    }

    printf("%.10lf",res);

    return 0;
}
