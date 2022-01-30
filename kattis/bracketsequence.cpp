#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 3e5 + 5;
const int M = 1e9 + 7;

int n;
char S[N];
vector<long> vec;

int main() {
    scanf("%d", &n);

    vec.emplace_back(0);
    for(int i = 1; i <= n; i++) {
        scanf(" %s", S + 1);
        if(S[1] == '(') {
            vec.emplace_back(vec.size() & 1);
            continue;
        }

        long val = 0;
        if(S[1] == ')') {
            val = vec.back();
            vec.pop_back();
        } else for(int j = 1; S[j] != '\0'; j++)
            val = val * 10 + (S[j] - '0');
        if(vec.size() & 1) vec.back() = (vec.back() + val) % M;
        else vec.back() = (vec.back() * val) % M;
    }
    printf("%lld\n", vec[0]);

    return 0;
}