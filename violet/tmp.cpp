#include <iostream>
#include <cstdio>
#include <cmath>
#include <set>
#include <map>
#include <queue>
#include <bitset>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#define Rep(i,a) for(int i = 0; i < a; i++)
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define dep(i,a,b) for(int i = a; i >= b; i--)
#define ab(a) ((a) > 0 ? (a) : -(a))
#define mp(a,b) make_pair(a,b)
#define pb(a) push_back(a)
using namespace std;
typedef long long LL;
typedef long long ll;
typedef unsigned long long uLL;
int n;
double r;
LL x, y;
void calc(ll a, ll b , ll x, ll y, ll &p , ll &q)
{
        if (a==0) {
           p = 1; q = y/x+1; return ;
        }
        ll k = y/x+1;
        if (k * a < b){
              q = y/x+1; p = a * q / b +1;
              return ;
        }
        ll t = min(y/x, b/a);
        calc(y-t*x, x, b-t*a, a , q, p);
        q += t*p;
        return ;
}

LL gcd(LL a, LL b){
  if (a == 0) return b;
  return b ? gcd(b, a % b) : a;
}
void work(){
  if (r == 0) printf("1\n");
  rep(i,1,n + 1) r *= 10;
  LL a, b, c, d;
  a = (LL)r - 5, c = (LL)r + 5;if (a < 0) a = 0;
  b = 1; rep(i,1,n + 1) b *= 10;
  d = b;
  LL t = gcd(a,b);
  a /= t, b /= t;
  calc(a, b, c, d, x, y);
  printf("%lld\n",b < y ? b : y);
}
int main(){
  while (scanf("%d%lf",&n,&r) == 2) work();
}