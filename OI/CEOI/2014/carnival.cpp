#include <bits/stdc++.h>
 
using namespace std;
 
const int N = 155;
 
int ask(vector<int> &v, int ret = 0) {
    if(v.empty()) return 0;
    printf("%d ", v.size());
    for(int i : v) printf("%d ", i);
    printf("\n"), fflush(stdout);
    scanf("%d", &ret);
    return ret;
}
 
int n, a[N];
 
int main() {
    scanf("%d", &n);
    vector<int> vec = {1};
    for(int i = 2; i <= n; i++) {
        vector<int> tmp = vec;
        tmp.emplace_back(i);
        if(ask(tmp) == tmp.size()) vec = tmp;
    }
    int cnt = n;
    for(int i = 1; i <= vec.size(); i++) a[vec[i-1]] = i, --cnt;
    for(int i = 1; i <= vec.size(); i++) {
        vector<int> now;
        for(int j = 1; j <= vec.size(); j++) if(j != i)
            now.emplace_back(vec[j-1]);
        while(cnt) {
            int l = 1, r = n;
            while(l < r) {
                int mid = (l + r) >> 1;
                vector<int> v = now;
                for(int j = 1; j <= mid; j++) if(!a[j] && j != vec[i - 1])
                    v.emplace_back(j);
                if(ask(v) == vec.size()) r = mid;
                else l = mid + 1;
            }
            vector<int> v = now;
            for(int j = 1; j <= r; j++) if(!a[j])
                v.emplace_back(j);
            if(ask(v) == vec.size()) a[r] = i, --cnt;
            else break;
        }
    }
    printf("0 ");
    for(int i = 1; i <= n; i++) printf("%d ", a[i]);
    printf("\n"), fflush(stdout);
 
    return 0;
}