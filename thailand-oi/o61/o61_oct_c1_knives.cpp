// [ [PP][-PPP][PPPP][xxxxxxxx] ] 
#include <bits/stdc++.h>

#define long long long
#define iii tuple<char, int, int>

using namespace std;

const int N = 1<<20;

int n, L, q;
int ps[N+5];
long val[N+5], lz[N<<1];
vector<iii> ask;

void push(int p, int l, int r) {
       if(lz[p]) {
              if(l == r) val[l] += lz[p];
              else {
                     lz[p<<1] += lz[p];
                     lz[p<<1|1] += lz[p];
              }
              lz[p] = 0;
       }
}

void update(int x, int y, long k, int p = 1, int l = 0, int r = L) {
       push(p, l, r);
       if(x > r || l > y) return;
       if(x <= l && r <= y) {
              lz[p] += k;
              push(p, l, r);
              return;
       }
       int m = (l + r) >> 1;
       update(x, y, k, p<<1, l, m), update(x, y, k, p<<1|1, m+1, r);
}

long query(int x, int p = 1, int l = 0, int r = L) {
       push(p, l, r);
       if(l == r) return val[l];
       int m = (l + r) >> 1;
       if(x <= m) return query(x, p<<1, l, m);
       else return query(x, p<<1|1, m+1, r);
}

bool fuck;
vector<int> shit;
int vl[1005][20005];
int flip[1005];

int get(int x) { return lower_bound(shit.begin(), shit.end(), x) - shit.begin(); }

int main() {
       scanf("%d %d %d", &n, &L, &q);
       for(int i = 1; i <= q; i++) {
              char c;
              int a, b;
              scanf(" %c %d", &c, &a);
              if(c == 's') scanf("%d", &b);
              if(c == 'f') fuck = true;
              if(c == 'q') shit.emplace_back(a);
              ask.emplace_back(c, a, b);              
       }
       sort(shit.begin(), shit.end());
       shit.erase(unique(shit.begin(), shit.end()), shit.end());
       if(!fuck) {
              for(int i = 0; i <= L; i++) val[i] = 1LL*i*n;
              fill_n(ps, N+5, L);
              for(iii tup : ask) {
                     char c;
                     int a, b;
                     tie(c, a, b) = tup;
                     if(c == 's') {
                            ++a;
                            int nps = ((ps[a] - 1 + b) % L) + 1;
                            if(nps < ps[a]) {
                                   b = ps[a] - nps;
                                   update(0, nps, b);
                                   update(nps+1, nps+b, b-L);
                                   update(nps+b+1, L, b);
                            } else if(nps > ps[a]) {
                                   update(0, ps[a], -b);
                                   update(ps[a]+1, ps[a]+b, L-b);
                                   update(ps[a]+b+1, L, -b);
                            }
                            ps[a] = nps;
                     } else if(c == 'q') {
                            printf("%lld\n", query(a));
                     }
              }
       } else {
              for(int i = 1; i <= n; i++) {
                     ps[i] = L, flip[i] = 0;
                     for(int j = 0; j < shit.size(); j++)
                            vl[i][j] = shit[j];
              }
              for(iii tup : ask) {
                     char c;
                     int a, b;
                     c = get<0>(tup), a = get<1>(tup), b = get<2>(tup);
                     if(c == 's') {
                            ++a;
                            int nps = ((ps[a] - 1 + b) % L) + 1;
                            for(int j = 0; j < shit.size(); j++) {
                                   if(nps < ps[a]) {
                                          b = ps[a] - nps;
                                          if(shit[j] <= nps) vl[a][j] += b;
                                          else if(shit[j] <= nps+b) vl[a][j] += b-L;
                                          else vl[a][j] += b;
                                   } else {
                                          if(shit[j] <= ps[a]) vl[a][j] -= b;
                                          else if(shit[j] <= ps[a]+b) vl[a][j] -= b-L;
                                          else vl[a][j] -= b;
                                   }
                            }
                            ps[a] = nps;
                     } else if(c == 'q') {
                            long ans = 0;
                            for(int i = 1; i <= n; i++) {
                                   if(!flip[i]) ans += vl[i][get(a)];
                                   else {
                                          if(ps[i] == n) ans += L-vl[i][get(a)];
                                          else if(vl[i][get(a)] != L) ans += L-vl[i][get(a)];
                                          else ans += vl[i][get(a)];
                                   }
                            }
                            printf("%lld\n", ans);
                     } else {
                            ++a;
                            flip[a] ^= 1;
                     }
              }
       }

       return 0;
}