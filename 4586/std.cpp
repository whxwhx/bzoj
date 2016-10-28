#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long LL;

#define MAX_N 100000
#define MAX_VAL 10
#define MAX_TOT (MAX_N*MAX_VAL)

int N, X, Y, Z, rtype[MAX_TOT*2+1]; 
LL res1[MAX_TOT*2+1], res2[MAX_TOT*2+1];
vector<int> rows[MAX_TOT*2+1];

void dp(vector<int> &v, LL *results)
{
  LL M=v.size(), i=-2, prefcost_i=0, prefcost_j=0, prev_longrange=999999999999999LL;
  for (int j=1; j<M; j+=2) {
    if (j>1) prefcost_j += Z*abs(v[j-2]-v[j-1]);
    if (j>1) prev_longrange += Z*abs(v[j-2]-v[j-1]);
    while (i+2 < j && X+Y <= Z*abs(v[j]-v[i+2])) {
      i += 2;
      if (i>0) prefcost_i += Z*abs(v[i]-v[i-1]);
      prev_longrange = min(prev_longrange, X+Y+prefcost_j-prefcost_i+(i>0?results[i-1]:0));
    }
    results[j] = min(prev_longrange, Z*abs(v[j]-v[j-1]) + (j>1?results[j-2]:0));
  }
}

LL solve(vector<int> &v, int ecost)
{
  LL M = v.size(), best;
  if (M == 0) return 0; 
  if (M == 1) return ecost; // cost of insert/delete for just single item
  dp(v, res1);
  reverse(v.begin(), v.end()); 
  dp(v, res2); 
  reverse(res2, res2+M);
  if (M%2 == 0) best = res1[M-1]; // even: all matched; only 1 DP pass needed
  else { // odd: one left out -- piece together prefix + missing item + suffix
    best = ecost + min(res1[M-2], res2[1]);
    for (int i=2; i<=M-3; i+=2) best = min(best, res1[i-1] + ecost + res2[i+1]);
  }
  return best;
}

int main(void)
{
  ifstream fin ("t.in");
  fin >> N >> X >> Y >> Z;
  for (int last_d=0, level=MAX_TOT, i=0; i<N; i++) {
    int a, b, m, d;
    fin >> a >> b;
    d = (max(a,b)==a) ? +1 : -1;
    m = max(a,b) - min(a,b); 
    while (m-- > 0) {
      if (last_d == d) level += d;
      if (rtype[level]==0) rtype[level] = d;
      rows[level].push_back(i);
      last_d = d;
    }
  }
  fin.close();
  
  ofstream fout ("t.out");
  LL total = 0;
  for (int level=0; level<MAX_TOT*2+1; level++) 
    total += solve(rows[level], rtype[level]>0 ? Y : X);
  fout << total << "\n";
  fout.close();

  return 0;
}