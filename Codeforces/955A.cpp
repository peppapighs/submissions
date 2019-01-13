#include <bits/stdc++.h>

using namespace std;

int main()
{
    int hr,m;
    scanf("%d%d",&hr,&m);
    double h,d,c,n;
    scanf("%lf%lf%lf%lf",&h,&d,&c,&n);
    if(hr>=20) {
        printf("%.4lf",c*0.8*ceil(h/n));
    } else {
        int w = ((19-hr)*60)+(60-m);
        int h2 = h + (w*d);
        double p1 = c*ceil(h/n);
        double p2 = c*0.8*ceil(h2/n);
        printf("%.4lf",min(p1,p2));
    }

    return 0;
}
