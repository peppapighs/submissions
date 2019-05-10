#include <bits/stdc++.h>

using namespace std;

const int N = 1e5+5;

int n, A[N], freq[N];
multiset<int> S;

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%d", A+i);
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        if(freq[A[i]]) S.erase(S.find(freq[A[i]]));
        ++freq[A[i]];
        S.emplace(freq[A[i]]);
        if(S.size() == 1) ans = i;
        if(S.size() == 2) {
            if(*S.begin() == 1) ans = i;
            if(*S.begin() + 1 == *S.rbegin()) ans = i;
        }
        if(*S.begin() == 1 && *next(S.begin()) == *S.rbegin()) ans = i;
        if(*S.begin() + 1 == *S.rbegin() && *S.begin() == *next(S.rbegin())) ans = i;
    }
    printf("%d\n", ans);

    return 0;
}