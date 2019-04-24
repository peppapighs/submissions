#include <bits/stdc++.h>

#define pii pair<double, int>
#define x first
#define y second

using namespace std;

const int N = 5e5+5;

int n, w, S[N], Q[N];
int pos[N];
vector<pii> V;

int main() {
    iota(pos, pos+N, 0);
    scanf("%d %d", &n, &w);
    for(int i = 1; i <= n; i++) {
        scanf("%d %d", S+i, Q+i);
        V.emplace_back(1.0 * S[i] / Q[i], i);
    }
    sort(V.begin(), V.end());
    priority_queue<pii> PQ;
    int sz = 0, idx = 0;
    double sum = 0, cost = 0;
    for(int i = 1; i <= (int)V.size(); i++) {
        pii v = V[i-1];
        sum += Q[v.y];
        PQ.emplace(Q[v.y], v.y);
        while(sum * v.x > w) {
            sum -= PQ.top().x;
            PQ.pop();
        }
        if((int)PQ.size() >= sz) {
            if((int)PQ.size() > sz) {
                sz = (int)PQ.size(), idx = i;
                cost = sum * v.x;
            } else if(sum * v.x < cost) {
                idx = i;
                cost = sum * v.x;
            }
        }
    }
    printf("%d\n", sz);
    PQ = priority_queue<pii>();
    sum = 0;
    for(int i = 1; i <= idx; i++) {
        pii v = V[i-1];
        sum += Q[v.y];
        PQ.emplace(Q[v.y], v.y);
        while(sum * v.x > w) {
            sum -= PQ.top().x;
            PQ.pop();
        }
    }
    while(!PQ.empty()) {
        printf("%d\n", PQ.top().y);
        PQ.pop();
    }
    
    return 0;
}
