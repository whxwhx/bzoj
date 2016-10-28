#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int N = 52, M = 2010, NUM = 110;
int f[N][NUM][M], g[N][M], w[N];
#define pb(a) push_back(a)
#define mp(a,b) make_pair(a,b)
typedef pair<int, int> node;
typedef vector<node>::iterator vit;
vector<node> son[N];
char tp[N];
int cost[N], num[N], n, m, fa[N], ans = 0;
void init(){
	rep(i,1,n) if (tp[i] == 'B')
		rep(j,0,num[i]){
			int ed = m - j * cost[i];
			rep(k,0,ed) f[i][j][k] =min(k / cost[i], num[i] - j) * w[i], ans = max(ans, f[i][j][k]);
		}
}
#define reg(i,x) for(vit i = son[x].begin(); i != son[x].end(); i++)
#define v ((*i).first)
#define vm ((*i).second)
void dp(int x){
	if (tp[x] == 'B') return;
	num[x] = NUM;
	reg(i,x) dp(v), num[x] = min(num[x], num[v] / vm), cost[x] += cost[v] * vm;

	//calc
	rep(j,0,num[x]){
		//calc_g
		int t = 0;
		reg(i,x){
			++t;
			rep(k,0,m - cost[x] * j){
				g[t][k] = 0;
				rep(t1, 0, k)
					g[t][k] = max(g[t][k], g[t - 1][k - t1] + f[v][j * vm][t1]);
			}
		}
		//calc_f
		rep(i,0,j) 
			rep(k,0,m - cost[x] * j) 
				f[x][i][k + (j - i) * cost[x]] = max(f[x][i][k + (j - i) * cost[x]], g[t][k] + (j - i) * w[x]), ans = max(ans, f[x][i][k + (j - i) * cost[x]]);
	}
}
int main(){
	scanf("%d %d",&n, &m);
	rep(i,1,n){
		scanf("%d ",&w[i]);
		tp[i] = getchar();
		while (tp[i] != 'A' && tp[i] != 'B') tp[i] = getchar();
		if (tp[i] == 'A'){
			int c; scanf("%d",&c);
			rep(j,1,c) {
				int t1, t2; scanf("%d %d", &t1, &t2);
				son[i].pb(mp(t1, t2));
				fa[t1] = i;
			}
		}else
			scanf("%d %d", &cost[i], &num[i]);
	}
	init();
	rep(i,1,n) if (!fa[i]) dp(i);
	printf("%d\n",ans);
}