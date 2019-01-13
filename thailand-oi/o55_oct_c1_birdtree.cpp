#include <bits/stdc++.h>

using namespace std;

int T;

int main() {
        scanf("%d", &T);
        while(T--) {
                char s[25];
                scanf(" %s", s+1);
                int i = 1, a = 0, b = 0;
                while(s[i] != '/') a = (a*10) + s[i++] - '0';
                ++i;
                while(s[i]) b = (b*10) + s[i++] - '0';
                vector<char> V;
                while(a != 1 || b != 1) {
                        if(a > b) {
                                V.emplace_back('R');
                                swap(a, b);
                                b -= a;
                        } else {
                                V.emplace_back('L');
                                swap(a, b);
                                a -= b;
                        }
                }
                for(int c : V) printf("%c", c);
                printf("\n");
        }

        return 0;
}
