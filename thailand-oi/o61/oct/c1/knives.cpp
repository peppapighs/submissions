#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 1e6+5;

void update(long t[], int x, int k) { for(int i = x+1; i < N; i += i & -i) t[i] += k; }

long query(long t[], int x) {
    long ret = 0;
    for(int i = x+1; i; i -= i & -i) ret += t[i];
    return ret;
}

long get(long t[], int x) { return query(t, x) - query(t, x-1); }

int n, l, q, fcnt;
bool flip[N];
long t[3][N]; //Position of knives, Not Flip, Flip

/* P_i = Position of the bottom of the knife, x = Query position

For non-flip knives :
P_i >= x : x - P_i + L
P_i < x : x - P_i

For flip knives :
P_i > x : P_i - x
P_i <= x : P_i - x + L

Sum of these are the answer of each query
*/

int main() {
    scanf("%d %d %d", &n, &l, &q);
    for(int i = 1; i <= n; i++) {
        update(t[0], i, -l);
        update(t[1], l, 1);
    }
    for(int i = 1; i <= q; i++) {
        char T;
        int a, b;
        scanf(" %c %d", &T, &a);
        if(T == 's') {
            ++a;
            scanf("%d", &b);
            int now = get(t[0], a), next;
            if(!flip[a]) now *= -1;
            update(t[flip[a]+1], now, -1);
            next = now + b;
            if(!flip[a]) next = (next - 1) % l + 1;
            else next %= l;
            update(t[0], a, (flip[a] ? 1ll : -1ll) * next - get(t[0], a));
            update(t[flip[a]+1], next, 1);
        } else if(T == 'f') {
            ++a;
            int now = get(t[0], a), next;
            if(!flip[a]) now *= -1;
            update(t[flip[a]+1], now, -1);
            if(!flip[a] && now == l) next = 0;
            else if(flip[a] && now == 0) next = l;
            else next = now;
            flip[a] ^= 1;
            if(flip[a]) ++fcnt;
            else --fcnt;
            update(t[0], a, (flip[a] ? 1ll : -1ll) * next - get(t[0], a));
            update(t[flip[a]+1], next, 1);
        } else {
            long sum = query(t[0], n);
            long geq = query(t[1], l) - query(t[1], a-1);
            long leq = query(t[2], a);
            printf("%lld\n", 1ll*a*(n - 2*fcnt) + sum + 1ll*l*(geq + leq));
        }
    }

    return 0;
}