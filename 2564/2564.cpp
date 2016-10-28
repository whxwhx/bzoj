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
#define Rep(i,a) for(int i = 0; i < (a); i++)
#define rep(i,a,b) for(int i = (a); i <= (b); i++)//(a)!
#define dep(i,a,b) for(int i = (a); i >= (b); i--)
#define ab(a) ((a) > 0 ? (a) : -(a))
#define mp(a,b) make_pair((a),(b))
#define pb(a) push_back(a)
using namespace std;
typedef long long LL;
typedef unsigned long long uLL;
const int N = 100010;
struct point{ int x, int y; }a[N], b[N];
int main(){
	int n, m; scanf("%d%d",&n,&m);
	rep(i,1,n) scanf("%d%d",&a[i].x,&a[i].y);
	rep(i,1,m) scanf("%d%d",&b[i].x,&b[i].y);
	calc(a, n), calc(b, m);
}