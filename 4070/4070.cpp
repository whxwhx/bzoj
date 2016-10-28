#include <iostream>
#include <cstdio>
#include <cmath>
#include <queue>
#include <algorithm>
using namespace std;
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
const int N = 30000 + 10, M = 6000000;
int b[N], p[N], c[N], cl = 0;

struct edge{
	int to, pre, c;
}e[M + N];
#define reg(i,a) for(int i=u[a];i;i=e[i].pre)
#define v e[i].to
#define ec e[i].c
int u[M], l = 0;
void ins(int a, int b, int c){
	//cout <<a<<' '<<b<<' '<<c<<endl;
	e[++l] = (edge){b, u[a], c}, u[a] = l;
}

int h[M], bel[M], maxnode;
int qn, n, m, pos[200];
typedef pair<int, int> node;
priority_queue<node> q;
#define mp(a,b) make_pair(a,b)
void bfs(){
	int l = 0, r = 1, S = b[1], T = b[2];
	rep(i,1,maxnode) h[i] = -1;
	h[S] = 0;
	q.push(mp(0, S));
	while (!q.empty()){
		int x = q.top().second;
		while (h[x] < -q.top().first){
			q.pop(); if (q.empty()) break;
			x = q.top().second;
		}
		if (q.empty()) break; else q.pop();
		reg(i,x) 
			if (h[v] == -1 || h[v] > h[x] + ec) 
				h[v] = h[x] + ec, q.push(mp(-h[v], v));//, cout <<v<<endl;
		if (bel[x]){
			int p = bel[x], j = x - pos[p], t = pos[p] + j - p;
			if (j - p >  0 && (h[t] == -1 || h[t] > h[x] + 1))
				h[t] = h[x] + 1, q.push(mp(-h[t], t));
			t = pos[p] + j + p;
			if (j + p <= n && (h[t] == -1 || h[t] > h[x] + 1))
				h[t] = h[x] + 1, q.push(mp(-h[t], t));
			if (h[j] == -1 || h[j] > h[x]) 
				h[j] = h[x], q.push(mp(-h[j], j));
		}
	}
	//rep(i,1,maxnode) cout <<i<<' '<<h[i]<<endl;
	printf("%d\n",h[T]);
}
void build_sqrtn(){
	maxnode = n;
	rep(i, 1, cl) if(c[i] <= qn){
		int p = c[i];
		pos[p] = n * i;
		maxnode = n * (i + 1);
		rep(j, 1, n){
			bel[pos[p] + j] = p;
			//if (j - p > 0) ins(pos[p] + j, pos[p] + j - p, 1);
			//if (j + p <= n) ins(pos[p] + j, pos[p] + j + p, 1);
			//ins(pos[p] + j, j, 0);
		}
	}else break;
	rep(i,1,m)if (p[i] <= qn) 
		ins(b[i], pos[p[i]] + b[i], 0); //m edges
}
void build(){
	rep(i,1,m) if (p[i] > qn){
		int t = 0;
		for(int j = b[i] - p[i]; j >  0; j -= p[i]) ins(b[i], j, ++t);//a1
		t = 0;
		for(int j = b[i] + p[i]; j <= n; j += p[i]) ins(b[i], j, ++t);//a2
		//a1 + a2 == msqrt(n) edges
	}
}
int main(){
	scanf("%d%d",&n,&m);
	rep(i,1,m) scanf("%d%d",&b[i],&p[i]), c[++cl] = p[i], b[i]++;
	
	sort(c + 1, c + cl + 1);
	cl = (int)(unique(c + 1, c + cl + 1) - c) - 1;
	
	qn = (int)(sqrt(n)); if (!qn) qn++;
	build_sqrtn();
	build();
	bfs();
	return 0;
}
