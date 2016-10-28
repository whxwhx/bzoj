#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i = (a); i <= (b); i++)
using namespace std;
const int N = 210, M = 2010;
struct edge{
	int to, pre;
}e[M * 4];
int u[N * 2];
int l = 0;
void ins(int a, int b){
	e[++l] = (edge){b, u[a]}, u[a] = l;
}
#define reg(i,a) for(int i = u[a]; i; i = e[i].pre)
#define v e[i].to
int mark[N * 2], s[N * 2], top = 0;
bool dfs(int x){
	s[++top] = x;
	mark[x] = 1, mark[x ^ 1] = 0;
	reg(i,x) if (mark[v] == -1) {
		if (!dfs(v)) return false;
	} else if (mark[v] == 0) return false;
	return true;
}
void work(){
	int n, m; scanf("%d%d",&n,&m);
	l = 0;
	rep(i,2,n << 1 | 1) u[i] = 0;
	rep(i,1,m){
		int t1, c1, t2, c2, x;
		
		char c = getchar();
		while (c != 'm' && c != 'h') c = getchar();
		if (c == 'h') t1 = 0; else t1 = 1;
		while (c < '0' || c > '9') c = getchar();
		x = 0;
		while (c >='0' && c <='9') x = x * 10 + c - '0', c = getchar();
		c1 = x;

		c = getchar();
		while (c != 'm' && c != 'h') c = getchar();
		if (c == 'h') t2 = 0; else t2 = 1;
		while (c < '0' || c > '9') c = getchar();
		x = 0;
		while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
		c2 = x;
	
		ins(c1 << 1 | (!t1), c2 << 1 | t2);
		ins(c2 << 1 | (!t2), c1 << 1 | t1);
	}
	rep(i,1,n) mark[i << 1] = mark[i << 1 | 1] = -1;
	rep(i,1,n) if (mark[i << 1] == -1){
			top = 0;
		if (!dfs(i << 1)){
			rep(j,1,top) mark[s[j]] = mark[s[j] ^ 1] = -1;
			if (!dfs(i << 1 | 1)) {printf("BAD\n");return;}
		}
	}
	printf("GOOD\n");
}
int main(){
	int t; scanf("%d",&t);
	while (t--) work();
}