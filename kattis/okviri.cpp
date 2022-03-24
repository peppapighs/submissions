#include <bits/stdc++.h>

using namespace std;

const int N = 25;

int n;
char S[N];

int main() {
    scanf(" %s", S);
    n = strlen(S);

    for(int step = 0; step < 5; step++) {
        if(step == 0 || step == 4) {
            for(int i = 0; i < n; i++) {
                if((i + 1) % 3 == 0)
                    printf("..*.");
                else printf("..#.");
            }
            printf(".\n");
        } else if(step == 1 || step == 3) {
            for(int i = 0; i < n; i++) {
                if((i + 1) % 3 == 0)
                    printf(".*.*");
                else printf(".#.#");
            }
            printf(".\n");
        } else {
            for(int i = 0; i < n; i++) {
                if((i + 1) % 3 == 0)
                    printf("*.%c.", S[i]);
                else {
                    if(i && i % 3 == 0)
                        printf("*.%c.", S[i]);
                    else printf("#.%c.", S[i]);
                }
            }
            if(n % 3 == 0) printf("*\n");
            else printf("#\n");
        }
    }

    return 0;
}