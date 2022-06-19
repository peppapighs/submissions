#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 1e5 + 5;

char S1[N], S2[N];
vector<int> A, B;

void solve(char *S, vector<int> &bit) {
    vector<int> carry = {0};
    bit.emplace_back(1);

    for (int i = 1; S[i] != '\0'; i++) {
        if (S[i] == '1')
            bit.emplace_back(0), carry.emplace_back(0);
        if (S[i] == '2')
            bit.emplace_back(0), carry.emplace_back(1);
        if (S[i] == 'U') {
            int now = carry.back() / 2;
            bit.back() += carry.back() % 2;
            if (bit.back() < 0)
                bit.back() = 1, --now;
            bit.pop_back(), carry.pop_back();
            carry.back() += now;
        }
        if (S[i] == 'L')
            --carry.back();
        if (S[i] == 'R')
            ++carry.back();
    }

    for (int i = bit.size() - 1; ~i; i--) {
        bit[i] += carry[i] % 2;
        if (i) {
            carry[i - 1] += carry[i] / 2;
            if (bit[i] < 0)
                bit[i] = 1, --carry[i - 1];
        }
    }
}

int main() {
    scanf("%s %s", S1 + 1, S2 + 1);
    solve(S1, A), solve(S2, B);

    long pre_A = 0, pre_B = 0, ans = 1e18;
    for (int i = 1; i <= min(A.size(), B.size()); i++) {
        pre_A = 2ll * pre_A + A[i - 1], pre_B = 2ll * pre_B + B[i - 1];
        long now = abs(pre_A - pre_B) + (int)A.size() + (int)B.size() - 2ll * i;
        ans = min(ans, now);
        if (ans < now)
            break;
    }
    printf("%lld\n", ans);

    return 0;
}