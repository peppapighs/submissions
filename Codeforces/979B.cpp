#include <bits/stdc++.h>

using namespace std;

int n;
map<char,int> m;

int moc(string s) {
    m.clear();
    for(int i=0;i<s.length();i++) {
        m[s[i]]++;
    }
    int oc=0;
    for(map<char,int>::iterator it=m.begin();it!=m.end();it++) {
        if(it->second>oc) {
            oc=it->second;
        }
    }
    return oc;
}

int cal(int l,int o) {
    if(n<l-o) {
        return o+n;
    } else if(l==o&&n==1) {
        return l-1;
    } else {
        return l;
    }
}

int main()
{
    scanf("%d",&n);
    string a,b,c;
    cin >> a >> b >> c;
    int occ[3] = {moc(a),moc(b),moc(c)};
    int res[3];
    string ans[3] = {"Kuro","Shiro","Katie"};

    if(n>=a.length()) {
        printf("Draw");
    } else {
        int x,y=-1;
        for(int i=0;i<3;i++) {
            res[i] = cal(a.length(),occ[i]);
            //printf("%d\n",res[i]);
            if(res[i]>y) {
                y = res[i];
                x=i;
            }
        }

        int cnt=0;
        for(int i=0;i<3;i++) {
            if(res[i]==y) {
                cnt++;
            }
        }
        if(cnt==1) {
            cout << ans[x];
        } else {
            cout << "Draw";
        }
    }

    return 0;
}
