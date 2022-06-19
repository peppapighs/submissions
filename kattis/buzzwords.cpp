#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 1e3 + 5;
const int P = 98765431;

string S;
long pw[N];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    pw[0] = 1;
    for (int i = 1; i < N; i++)
        pw[i] = pw[i - 1] * P;

    while (getline(cin, S), !S.empty()) {
        string str = "";
        for (char &c : S)
            if (c != ' ')
                str += c;

        for (int len = 1; len <= (int)str.size(); len++) {
            map<long, int> mp;
            long hsh = 0;
            for (int i = 0; i < len; i++)
                hsh = hsh * P + (long)str[i];
            ++mp[hsh];
            for (int i = len; i < (int)str.size(); i++) {
                hsh = hsh * P + (long)str[i] - str[i - len] * pw[len];
                ++mp[hsh];
            }

            int ans = 0;
            for (auto &p : mp)
                ans = max(ans, p.second);
            if (ans <= 1)
                break;
            else
                cout << ans << "\n";
        }
        cout << "\n";
    }

    return 0;
}