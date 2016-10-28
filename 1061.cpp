#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
using namespace std;
const int N = 10010;
struct edge{
	int to, pre, w, c;
}e[N * 6];
int l = 0, u[N];
void ins(int a, int b, int w, int c){
	e[++l] = (edge){b, u[a], w, c}, u[a] = l;
}
void insert(int a, int b, int w, int c){
	ins(a, b, w, c), ins(b, a, 0, -c);
}
#define v e[i].to
#define ec e[i].c
#define ew e[i].w
#define reg(i,a) for(int i = u[a]; i; i = e[i].pre)

int from[N], h[N], q[N], S, T;
bool spfa(){
	int l = 0, r = 1; 
}

void mcf(){

}

const int inf = 0x7fffffff;

int a[N];
int main(){
	int n, m; scanf("%d%d",&n,&m);
	rep(i,1,n) scanf("%d",&a[i]);
	rep(i,1,m){
		int s, t, c;
		scanf("%d%d%d",&s,&t,&c);
		insert(s - 1, t, inf, c);
	}
	S = n * 2 + 1, T = S + 1;
	rep(i,0,n){
		insert(i, n + i, )
		if (a[i] - a[i + 1] < 0) insert(); else insert();
	}
	while (spfa()) mcf();
}
