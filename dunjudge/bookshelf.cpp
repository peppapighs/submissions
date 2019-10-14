#include <bits/stdc++.h>

using namespace std;

int q;
map<int, int> pos;
deque<int> Q;

int main() {
    scanf("%d", &q);

    int counter = 0;
    while(q--) {
        int T, a;
        scanf("%d", &T);
        if(T == 1) {
            scanf("%d", &a);
            ++counter;
            pos[a] = 1 - counter; 
            Q.emplace_front(a);
        } else if(T == 2) {
            scanf("%d", &a);
            pos[a] = Q.size() + 1 - counter;
            Q.emplace_back(a);
        } else if(T == 3) {
            --counter;
            pos.erase(Q.front());
            Q.pop_front();
        } else if(T == 4) {
            pos.erase(Q.back());
            Q.pop_back();
        } else if(T == 5) {
            scanf("%d", &a);
            printf("%d\n", pos[a] + counter);
        } else {
            scanf("%d", &a);
            printf("%d\n", (int)Q.size() - (pos[a] + counter) + 1);
        }
    }

    return 0;
}