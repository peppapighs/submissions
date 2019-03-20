#include "recoverlib.h"
#include <cstdio>
#include <cstdlib>

static int n;
static int vals[3010];
static int found[3010];
static int query_count;

static void error_and_die(const char* msg)
{
  printf("%s\n",msg);
  exit(0);
}

int recover_init()
{
  scanf("%d",&n);
  for(int i=0; i<n; i++) {
    scanf("%d",&vals[i]);
  }
  for(int i=0; i<=n; i++) {
    found[i] = 0;
  }
  query_count = 0;

  return n;
}

int recover_query(int L, int R, int D)
{
  if(query_count > 222222) {
    error_and_die("ERROR: too many calls");
  }
  if((L < 1) || (R > n) || (L > R)) {
    error_and_die("ERROR: incorrect calls");
  }
  query_count++;

  int count = 0;
  for(int i=L-1; i<=R-1; i++) {
    if((vals[i] % D == 0) && (vals[i] != D)) {
      if(found[vals[i]] != query_count) {
        count++;
        found[vals[i]] = query_count;
      }
    }
  }
  return count;
}

void recover_answer(int Ar[])
{
  for(int i=0; i<n; i++) {
    if(Ar[i+1] != vals[i]) {
      printf("%d, %d, %d\n",i,Ar[i+1],vals[i]);
      error_and_die("ERROR: incorrect answer");
    }
  }
  printf("OK\n");
  printf("%d\n", query_count);
  exit(0);
}
