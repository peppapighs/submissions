#include <bits/stdc++.h>
 
using namespace std;
 
const int N = 6e5+5;
 
struct Trie {
    int t[N][3], tag[N], ptr = 1;

    void add(char *S, int p = 1, int i = 1) {
        if(S[i] == '\0') return void(tag[p] = 1);
        int &now = t[p][S[i] - 'a'];
        if(!now) now = ++ptr;
        add(S, now, i + 1);
    }

    bool find(char *S, int p = 1, int i = 1, int dif = 0) {
        if(S[i] != '\0') {
            int now = S[i] - 'a';
            if(t[p][now] && find(S, t[p][now], i + 1, dif))
                return true;
            if(!dif)
                for(int j = 0; j < 3; j++) if(j != now && t[p][j] && find(S, t[p][j], i + 1, 1))
                    return true;
        } else if(dif && tag[p]) return true;
        return false;
    }
} trie;

int n, m;
char S[N];
 
int main() {
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; i++) {
        scanf(" %s", S + 1);
        trie.add(S);
    } 
    for(int i = 1; i <= m; i++) {
        scanf(" %s", S + 1);
        if(trie.find(S)) printf("YES\n");
        else printf("NO\n");
    }
 
    return 0;
}