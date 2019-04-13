#include <bits/stdc++.h>

using namespace std;

int n;
char S[105];
vector<int> A, B;

void solve(int idx) {
    memset(S, 0, sizeof S), A.clear(), B.clear();
    scanf(" %s", S+1);
    n = strlen(S+1);
    for(int i = 1; i <= n; i++) S[i] -= (int)'0';
    for(int i = n; i; i--) {
        if((S[i] == '0' || S[i] == '1') && i > 1) {
            int pos = i-1;
            S[i] += 10;
            while(S[pos] == 0) S[pos--] = 9;
            --S[pos];
        }
        bool valid = false;
        for(int j = 1; j < S[i]; j++) {
            if(j == 4 || S[i] - j == 4 || S[i] - j > 9) continue;
            A.emplace_back(j), B.emplace_back(S[i] - j); 
            valid = true;
            break;
        }
        if(!valid) A.emplace_back(0), B.emplace_back(S[i]);
    }
    while(!A.back()) A.pop_back();
    while(!B.back()) B.pop_back();
    reverse(A.begin(), A.end()), reverse(B.begin(), B.end());
    printf("Case #%d: ", idx);
    for(int d : A) printf("%d", d);
    printf(" ");
    for(int d : B) printf("%d", d);
    printf("\n");
}

int T;

int main() {
    scanf("%d", &T);
    for(int i = 1; i <= T; i++) solve(i);

    return 0;
}
