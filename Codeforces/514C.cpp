#include <bits/stdc++.h>

using namespace std;

const int N = 6e5+5;
const int P = 98765431;

int n, m;
long mpow[N];
char S[N];
set<long> st;

int main() {
    mpow[0] = 1;
    for(int i = 1; i < N; i++) mpow[i] = mpow[i-1] * P;

    scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; i++) {
        long hsh = 0;
        scanf(" %s", S + 1);
        for(int j = 1; S[j] != '\0'; j++) hsh += S[j] * mpow[j-1];
        for(int j = 1; S[j] != '\0'; j++) {
            hsh -= S[j] * mpow[j-1];
            for(int k = 'a'; k <= 'c'; k++) st.emplace(hsh + k * mpow[j-1]);
            hsh += S[j] * mpow[j-1];
        }
    }
    for(int i = 1; i <= m; i++) {
        long hsh = 0;
        scanf(" %s", S + 1);
        for(int j = 1; S[j] != '\0'; j++) hsh += S[j] * mpow[j-1];
        if(st.find(hsh) != st.end()) printf("YES\n");
        else printf("NO\n");
    }

    return 0;
}