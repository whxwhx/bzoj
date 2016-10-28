#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;

const int S = (1 << 10) - 1, inf = (1 << 16) * 100 + 1, Q = 11 * 11 * (S + 1); 
int f[11][11][S + 1], a[11][11], pre[11][11][S + 1];
bool inq[11][11][S + 1];

struct F{
	int i, j, s;
}q[Q], pre1[11][11][S + 1], pre2[11][11][S + 1];

int dx[5], dy[5], vis[11][11][S], Vis[11][11], ks;
void dfs(int i, int j, int s){
	vis[i][j][s] = Vis[i][j] = 1;
	if (pre1[i][j][s].i == -1) return; else{
		F x = pre1[i][j][s];
		if (!vis[x.i][x.j][x.s]) dfs(x.i, x.j, x.s);
		x = pre2[i][j][s];
		if (!vis[x.i][x.j][x.s]) dfs(x.i, x.j, x.s);
	}
}

int ans = inf, n, m;
void calc(){
	rep(i,1,n) 
		rep(j,1,m)
			if (f[i][j][ks] == ans) {dfs(i,j,ks); return;}
}
int main(){
	scanf("%d%d",&n,&m);
	rep(i,1,n) rep(j,1,m) scanf("%d",&a[i][j]);
	rep(i,1,n) rep(j,1,m) rep(k,0,S) f[i][j][k] = inf, inq[i][j][k] = 0, pre1[i][j][k] = pre2[i][j][k] = (F){-1, -1, -1}, vis[i][j][k] = Vis[i][j] = 0;
	int k = 0, l = 0, r = 0;
	rep(i,1,n) rep(j,1,m) if (!a[i][j]) 
		k++, 
		f[i][j][1 << (k - 1)] = f[i][j][0] = 0,
		q[r++] = (F){i, j, 1 << (k - 1)}, q[r++] = (F){i, j, 0},
		inq[i][j][1 << (k - 1)] = inq[i][j][0] = 1;
	else 
		f[i][j][0] = a[i][j],
		q[r++] = (F){i, j, 0},
		inq[i][j][0] = 1;


	dx[0] = 0 , dy[0] = 1;
	dx[1] = 0 , dy[1] = -1;
	dx[2] = -1, dy[2] = 0;
	dx[3] = 1 , dy[3] = 0;
	dx[4] = 0 , dy[4] = 0;


	ks = (1 << k) - 1;
	while (l != r){
		F x = q[l++]; inq[x.i][x.j][x.s] = 0, l %= Q;
		int ss = ks - x.s;
		while (true){
			int s = x.s + ss;
			rep(t,0,4){
				int i = x.i + dx[t], j = x.j + dy[t];
				if (i && j && i <= n && j <= m && f[i][j][s - x.s] < inf){ 
					if (f[x.i][x.j][x.s] + f[i][j][s - x.s] < f[i][j][s]){
						f[i][j][s] = f[x.i][x.j][x.s] + f[i][j][s - x.s];
						if (!inq[i][j][s]) q[r++] = (F){i,j,s}, inq[i][j][s] = 1, r %= Q;
						pre1[i][j][s] = x, pre2[i][j][s] = (F){i, j, s - x.s};
					}
					if (f[x.i][x.j][x.s] + f[i][j][s - x.s] < f[x.i][x.j][s]){
						f[x.i][x.j][s] = f[x.i][x.j][x.s] + f[i][j][s - x.s];
						if (!inq[x.i][x.j][s]) q[r++] = (F){x.i, x.j, s}, inq[x.i][x.j][s] = 1, r %= Q;
						pre1[x.i][x.j][s] = x, pre2[x.i][x.j][s] = (F){i, j, s - x.s};
					}
				}
			}
			if (ss == 0) break; else ss = (ss - 1) & (ks - x.s);
		}
	}



	rep(i,1,n) 
		rep(j,1,m)
			ans = min(ans, f[i][j][(1 << k) - 1]);
	printf("%d\n",ans);	

	calc();

	rep(i,1,n){
		rep(j,1,m){
			if (!a[i][j])
				printf("x");
			else if (!Vis[i][j]) 
				printf("_");
			else 
				printf("o");

		}
		printf("\n");
	}
	return 0;
}