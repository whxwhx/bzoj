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

const int N = 11000, M = 101000, N0 = 110, inf = N;

int S, T;
struct edge{
    int to, pre, w;
}e[M * 2];
int cur[N], u[N], l = 1;//l = 1!
#define ew e[i].w
#define v e[i].to
#define reg(i,a) for(int i = u[a]; i; i = e[i].pre)
#define ceg(i,a) for(int i = cur[a]; i; i = e[i].pre)
void ins(int a, int b, int w){
    e[++l] = (edge){b, u[a], w}, u[a] = l;
}
void insert(int a, int b, int w){//used insert to add an edge instead of using ins!
    ins(a, b, w), ins(b, a, 0);
}
int q[N], h[N];
bool bfs(){
    rep(i,S,T) h[i] = -1;
    int l = 0, r = 1; q[h[S] = 0] = S;
    while (l < r){
        int x = q[l++];
        reg(i,x) if (ew && h[v] == -1) h[v] = h[x] + 1, q[r++] = v;
    }
    return h[T] != -1;
}
int dfs(int x, int f){
    if (x == T || f == 0) return f;
    int used = 0, w;
    ceg(i,x)if (ew && h[v] == h[x] + 1){
        w = min(ew, f - used), w = dfs(v, w);
        ew -= w; if (ew) cur[x] = i;
        e[i^1].w += w;
        used += w; if (used == f) break;
    }
    if (!used) h[x] = -1;
    return used;
}
int dinic(){
    int ans = 0;
    while (bfs()){
        rep(i,S,T) cur[i] = u[i];
        ans += dfs(S, inf);
    }
    return ans;
}

char s[N0][N0];
int id[N0][N0], L = 0, a[N], b[N];
int dx[2] = {0, 1};
int dy[2] = {1, 0};

bool mS[N], mT[N];

void dfsS(int x){
	mS[x] = true;
	reg(i,x) if (ew && !mS[v]) dfsS(v);
}
void dfsT(int x){
	mT[x] = true;
	reg(i,x) if (!ew && !mT[v]) dfsT(v);
}

int main(){
	int n, m; scanf("%d%d",&n,&m);
	rep(i,1,n) scanf("%s",s[i] + 1);
	rep(i,1,n) s[i][0] = s[i][m + 1] = '#';
	rep(i,1,m) s[0][i] = s[n + 1][i] = '#';
	rep(i,1,n){
		rep(j,1,m) if (s[i][j] == '.'){
			L++;
			a[L] = i, b[L] = j;
			id[i][j] = L;
		}
	}
	
	S = 0, T = L + 1;
	rep(i,1,n) rep(j,1,m) if (s[i][j] == '.'){
			rep(d,0,1){
				int x1 = i + dx[d], y1 = j + dy[d];
				if (s[x1][y1] == '.'){
					if ((i ^ j) & 1)
						insert(id[i][j], id[x1][y1], 1);
					else 
						insert(id[x1][y1], id[i][j], 1);
				}
			}
	}

	int c1 = 0, c2 = 0;

	rep(i,1,n) rep(j,1,m) if (s[i][j] == '.'){
		if ((i ^ j) & 1) //注意用位运算的时候要多打括号！&会比^先算！
			insert(S, id[i][j], 1), c1++;
		else 
			insert(id[i][j], T, 1), c2++;
	}

	int flow = dinic();
	if (c1 == c2 && c1 == flow) {printf("LOSE\n");return 0;}

	printf("WIN\n");
	dfsS(S);
	dfsT(T);
	rep(i,1,L) if ((a[i] ^ b[i]) & 1){
		if (mS[i]) printf("%d %d\n",a[i],b[i]);
	}else {
		if (mT[i]) printf("%d %d\n",a[i],b[i]);
	}
	return 0;
}

/*
	这个游戏最严谨的描述是：
		后手有必胜策略当存在一个不含起点的最大匹配
		这样先手就会走到一个匹配点，后手顺着匹配走，
		先手总会走到匹配了的点，不然就得到了一个未匹配到未匹
		配的增广路
		
		如果不存在一个不含起点的最大匹配，先手必胜，
		先手始终顺着匹配边走，后手总会走到匹配了的点
		不然我们就可以把这个长度为偶数的增广轨取反就
		可以得到一个不含起点的最大匹配了

		从而证明后手有必胜策略当且仅当存在一个不含起点的最大匹配
	
	二分图如何判定存不存在一个不含点x的最大匹配？
		不在最大匹配上的肯定可以。。
		
		在最大匹配上的。。我们就要把S-->x这个流量想办法退掉，
		那么也就是经过x->S增广一个环。。
		也就是残量网络里找个S->x的路径。。
		也就是S经过未满的边能到达的左边节点都是存在一个不含他们的。。。
		
		然后x->T的话类似。。
		我们经过T->x增广一个环
		找一个x->T的路径。。
		能经过未满的边到达T的节点。。用反向边搜搜搜即可
*/