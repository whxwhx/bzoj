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
const int N = 500010, inf = 1000000000, mod = 1000000000 + 7;
int x[N], y[N], tmp = 0;
LL prod, ans;

int mn[N], mx[N], c1[N];

void mx(int x, int a){

}
void my(int x, int a){

}
void calc()){

}
int main(){
	int n; scanf("%d",&n);
	rep(i,1,n) scanf("%d",&x[i]);
	rep(i,1,n) scanf("%d",&y[i]);
	int t = 0;
	prod = y[i];
	dep(i,n,1){
		prod = max(prod, y[i]);
		prod *= x[i];
	 	t = i;
		if (prod >= inf) break;
	}
	ans = 1;
	rep(i,1,t - 1) ans = ans * x[i] % mod;
	ans = ans * (prod % mod) % mod;
	printf("%d\n",ans);
	int m; scanf("%d",&m);
	rep(i,1,m){
		int tp, pos, val; scanf("%d%d%d",&tp,&pos,&val);
		if (tp == 1) mx(pos, val);
		else if (tp == 2) my(pos, val);
		calc();
	}
	return 0;
}