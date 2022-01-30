#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 105;

char S[N];
vector<int> num;

bool prime(int x) {
    if(x < 2) return false;
    bool valid = true;
    for(int i = 2; i * i <= x; i++)
        valid &= (x % i != 0);
    return valid;
}

int main() {
    while(scanf(" %s", S + 1) != EOF) {
        if(S[1] == '0' || strlen(S + 1) > 10)
            return !printf("0\n");
        long now = 0;
        for(int i = 1; S[i] != '\0'; i++) {
            now = now * 10 + (S[i] - '0');
            if('0' > S[i] || S[i] > '9')
                return !printf("0\n");
        }
        if(now == 0 || now > (long)1e9)
            return !printf("0\n");
        num.emplace_back((int)now);
    }
    if(num.size() != 3) return !printf("0\n");
    if(num[0] % 2 == 0 && num[0] >= 3 && num[0] == num[1] + num[2] && prime(num[1]) && prime(num[2]))
        printf("1\n");
    else printf("0\n");

    return 0;
}