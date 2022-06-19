#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 5;

struct node {
    char d;
    int sz;
    node *par[20];
    node() {}
    node(char d) : d(d) {
        for (int i = 0; i <= 19; i++)
            par[i] = NULL;
    }
};

int ptr;
node *S[N];

void Init() {
    ptr = 0;
    S[0] = NULL;
}

void TypeLetter(char L) {
    ++ptr;
    S[ptr] = new node(L);
    S[ptr]->sz = S[ptr - 1] ? S[ptr - 1]->sz + 1 : 1;
    S[ptr]->par[0] = S[ptr - 1];
    for (int i = 1; i <= 19; i++)
        if (S[ptr]->par[i - 1])
            S[ptr]->par[i] = S[ptr]->par[i - 1]->par[i - 1];
}

void UndoCommands(int U) { S[++ptr] = S[ptr - U]; }

char GetLetter(int P) {
    int d = S[ptr]->sz - P - 1;
    node *now = S[ptr];
    for (int i = 19; ~i; i--)
        if (d >> i & 1)
            now = now->par[i];
    return now->d;
}
