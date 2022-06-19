#include <bits/stdc++.h>

#define pll pair<int, int>

using namespace std;

const int N = 1e5 + 5;

pll add(pll a, pll b) { return {a.first + b.first, a.second + b.second}; }
pll sub(pll a, pll b) { return {a.first - b.first, a.second - b.second}; }
pll mul(pll a, pll b) { return {a.first * b.first, a.second * b.second}; }

int q;
pll pm = {101, 103};
pll power[N];

int main() {
    power[0] = {1, 1};
    for (int i = 1; i < N; i++) {
        power[i] = mul(power[i - 1], pm);
    }
    scanf("%d", &q);
    while (q--) {
        int cnt = 0;
        string str, pat;
        cin >> pat >> str;
        pll hp = {0, 0}, win = {0, 0};
        for (int i = 0; i < pat.length(); i++) {
            hp = add(mul(hp, pm), {pat[i], pat[i]});
            win = add(mul(win, pm), {str[i], str[i]});
        }
        if (hp == win)
            cnt++;
        for (int i = pat.length(); i < str.length(); i++) {
            win = add(
                mul(sub(win, mul({str[i - pat.length()], str[i - pat.length()]},
                                 power[pat.length() - 1])),
                    pm),
                {str[i], str[i]});
            if (hp == win)
                cnt++;
        }
        printf("%d\n", cnt);
    }

    return 0;
}