#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
using namespace std;
const int N = 500010;

struct edge{
	int to, pre;
}e[N];
int u[N];
int l = 0;
void ins(int a, int b){
	e[++l] = (edge){b, u[a]}, u[a] = l;
}
#define reg(i,a) for(int i = u[a]; i; i = e[i].pre)
#define v e[i].to

char s[N];
int n, p[N];
void kmp(){
	p[1] = 0;
	rep(i,2,n){
		int j = p[i - 1];
		while (j && s[i] != s[j + 1]) j = p[j];
		if (s[i] == s[j + 1]) p[i] = j + 1; else p[i] = 0;
	}
}

int son[N];

int nex[N], pre[N], mx = 1;
void del(int x){
	if (nex[x] - pre[x] > mx) mx = nex[x] - pre[x];
	pre[nex[x]] = pre[x], 
	nex[pre[x]] = nex[x];
}

void dfs1(int x){
	del(x); reg(i,x) dfs1(v);
}

int ans;
void dfs(int x){
	if (mx <= x) {ans = x; return;} else {
		reg(i,x) if (v != son[x]) dfs1(v);
		dfs(son[x]);
	}
}
int main(){
	scanf("%s",s + 1); n = strlen(s + 1);
	kmp();
	rep(i,1,n) ins(p[i], i);
	for(int i = n; i; i = p[i]) son[p[i]] = i;
	rep(i,0,n) pre[i] = i - 1, nex[i] = i + 1;
	pre[0] = 0, nex[n] = n;
	ans = n;
	dfs(0);
	printf("%d\n",ans);
}