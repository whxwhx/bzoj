#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define dep(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef long long LL;
const int N = 500 + 10, M = 10000 + 10;
struct edge{
	int to, pre, c;
}e[M];
int l = 0, u[N];
void ins(int a, int b, int c){
	e[++l] = (edge){b, u[a], c}, u[a] = l;
}
#define ec e[i].c
#define v e[i].to
#define reg(i,a) for(int i = u[a]; i; i = e[i].pre)
char t[5];
int get(char *t){
	int l = strlen(t), ans = 0;
	rep(i,0,l - 1) ans = ans * 10 + (int)(t[i] - '0');
	return ans;
}
int f[N][N], n, m;
typedef pair<int, int> node;
#define mp(a,b) make_pair(a,b)
node q[N * N];
bool inq[N][N];
void spfa(int S){
	int l = 0, r = 1;
	q[l] = mp(S, 0);
	rep(i,1,n) rep(j,0,n) f[i][j] = -1, inq[i][j] = false;
	f[S][0] = 0;
	while (l < r){
		node x = q[l++]; 
		inq[x.first][x.second] = false, l %= N * N;
		reg(i,x.first) if (ec){
			int &t = f[v][x.second], fx = f[x.first][x.second];
			if (t == -1 || t > fx + ec) {
				t = fx + ec;
				if (!inq[v][x.second]) q[r++] = mp(v, x.second), r %= N * N, inq[v][x.second] = 1;
			}
		}else if (x.second + 1 < n){
			int &t = f[v][x.second + 1], fx = f[x.first][x.second];
			if (t == -1 || t > fx){
				t = fx;
				if (!inq[v][x.second + 1]) q[r++] = mp(v, x.second + 1), r %= N * N, inq[v][x.second + 1] = 1;
			}
		}
	}
}
int g[N];
node st[N];
LL calc(int i, int x){
	return 1LL * i * x + g[i];
}
int main(){
	scanf("%d%d",&n,&m);
	rep(i,1,m){
		int c, d;
		scanf("%d%d%s",&c,&d,t);
		if (t[0] == 'x') ins(c,d,0);
		else ins(c,d,get(t));
	}
	int Q; scanf("%d",&Q);
	rep(i,1,Q){
		LL ans1 = 0;
		int ans0 = 0;
		int a, b; scanf("%d%d",&a,&b);
		spfa(a);
		rep(i,0,n - 1) g[i] = f[b][i];
		int top = 0;
		bool flag1 = true;
		rep(i,0,n - 1) if (g[i] != -1) flag1 = false;

		if (flag1){
			printf("0 0\n");continue;
		}else if (g[0] == -1){
			printf("inf\n");continue;
		}else{
			dep(i,n - 1,0) if (g[i] != -1) {
				if (!top) st[top++] = mp(i, 1); 
				else{
					while (top && calc(i, st[top - 1].second) <= calc(st[top - 1].first, st[top - 1].second)) top--;
					if (!top) st[top++] = mp(i, 1);else
					{
						int k1 = st[top - 1].first, b1 = g[k1], k2 = i, b2 = g[i]; 
						int t1 = (b2 - b1) / (k1 - k2) + 1;
						st[top++] = mp(i,t1);
					}
				}
			}
			rep(i,1,top - 1){
				int t = st[i].second - st[i - 1].second;
				ans0 += t;
				ans1 += (1LL * calc(st[i - 1].first, st[i - 1].second) + calc(st[i - 1].first, st[i].second - 1)) * t / 2;
			}
			if (top == 1 || calc(st[top - 2].first, st[top - 1].second - 1) != g[0]) ans0++, ans1+=g[0];
		}
		printf("%d %lld\n",ans0,ans1);
	}
}
/*
	简要题解：
	  有k条特殊边的路径长度是kx+b
	  由于是最短路，显然最小的b才有意义
	  最短路只有n-1条边，k只有n-1种取值
	  dp+spfa求出每个k对应的最小b
	  然后显然在x取不同值时最优点不同。。而这个最短路肯定是单调递增的。。。
	  实际上就是若干y = kx + b (k > 0)的一个凸壳。。
	  随着x增大。。最优点肯定是k递减，b递增的。。
	  把这些直线按照这个顺序加入。。然后在栈里面维护出一个凸壳之后。。最后再统计答案
*/