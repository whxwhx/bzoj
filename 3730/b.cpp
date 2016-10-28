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

struct edge{
	int to, pre;
}e[N * 2];
int u[N];
int l = 0;
void ins(int a, int b){
	e[++l] = (edge){b, u[a]}, u[a] = l;
}
#define reg(i,a) for(int i = u[a]; i; i = e[i].pre)
#define v e[i].to

int a[N];
int qry(int x, int f, int k){
	//cout <<x<<' '<<f<<' '<<k<<endl;
	if (k == 0) return a[x];
	int ans = a[x];
	reg(i,x) if (v != f) ans += qry(v, x, k - 1);
	return ans;
}

int main(){
	int n, m; scanf("%d%d",&n,&m);
	rep(i,1,n) scanf("%d",&a[i]);
	rep(i,1,n - 1) {
		int a, b; scanf("%d%d",&a,&b);
		ins(a, b), ins(b, a);
	}
	int lastans = 0;
	rep(i,1,m){
		int op, x, k;
		//x ^= lastans, k ^= lastans;
		scanf("%d%d%d",&op,&x,&k);
		if (op == 1) a[x] = k;
		else printf("%d\n",lastans = qry(x, 0, k));
	}
	return 0;
}