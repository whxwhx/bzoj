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

int rt, sz[N], s[N], sum, vis[N];

int dfs(int x, int f){
	int ans = 1;
	reg(i,x) if (v != f) ans += dfs(v, x);
	return ans;
}
void getrt(int x, int f){
	sz[x] = 1, s[x] = 0;
	reg(i,x) if (v != f && !vis[v]){
		getrt(v, x);
		sz[x] += sz[v];
		s[x] = max(s[x], sz[v]);
	}
	s[x] = max(s[x], sum - sz[x]);
	if (s[x] < s[rt] || (s[x] == s[rt] && x < rt)) rt = x;
}

char S[10];
int main(){
	int n, m; scanf("%d%d",&n,&m);
	s[0] = n;
	rep(i,1,m) {
		scanf("%s",S);
		if (S[0] == 'A') {
			int a, b; scanf("%d%d",&a,&b);
			ins(a, b), ins(b, a);
		}else if (S[0] == 'Q'){
			int a; scanf("%d",&a);
			sum = dfs(a, 0);
			rt = 0, getrt(a, 0);
			cout <<rt<<endl;
		}
	}
}