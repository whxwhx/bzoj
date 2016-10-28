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
#define min(a,b) ((a) < (b) ? (a) : (b))
using namespace std;
typedef long long LL;
typedef unsigned long long uLL;
const int N = 100000 + 20;
struct node{
	node *trans[4], *par;
	int l;
}T[N * 2], *S = &T[0], *p = &T[0];
int tl = 0;
node *nn(){ return &T[++tl]; }
void add(int x){
	node *w = p;
	p = nn();p->l = w->l + 1;
	for(; w && !w->trans[x]; w = w->par) w->trans[x] = p;
	if (!w) p->par = S;
	else {
		node *q = w->trans[x];
		if (w->l + 1 == q->l) p->par = q;
		else {
			node *r = nn(); *r = *q, r->l = w->l + 1;
			p->par = q->par = r;
			for(; w && w->trans[x] == q; w = w->par) w->trans[x] = r;
		}
	}
}
LL n;
int c[5][5];
int f[64][5][5], g1[5][5], g[5][5];
pair<int, int> nd[N * 2];
char s[N];
int t1[N * 2][5];
int main(){
	scanf("%lld",&n);
	scanf("%s",s + 1); int l = strlen(s + 1);
	rep(i,1,l) add(s[i] - 'A');
	rep(i,0,3) rep(j,0,3) c[i][j] = n + 1;

	rep(i,1,tl) nd[i] = mp(T[i].l, i);
	sort(nd + 1, nd + tl + 1);
	rep(i,1,tl) rep(j,0,3) t1[i][j] = n + 2;
	rep(i,0,3) rep(j,0,3) c[i][j] = n + 2;

	rep(i,0,3) if (S->trans[i]) t1[(S->trans[i]) - T][i] = 1;
	rep(i,1,tl){
		node *u = &T[nd[i].second];
		rep(j,0,3)if (u->trans[j]){
			node *v = u->trans[j];
			rep(k,0,3) t1[v - T][k] = min(t1[v - T][k], t1[u - T][k] + 1);
		} else rep(k,0,3) c[k][j] = min(c[k][j], t1[u - T][k] + 1);
	}

	rep(i,0,3) rep(j,0,3) f[0][i][j] = c[i][j];
	rep(i,1,62){
		rep(j,0,3) rep(k,0,3) f[i][j][k] = n + 2;
		rep(j,0,3) 
			rep(k,0,3)
				rep(t,0,3)
					f[i][j][k] = min(f[i - 1][j][t] + f[i - 1][t][k] - 1, f[i][j][k]);// cout <<i<<' '<<j<<' '<<k<<' '<<f[i][j][k]<<endl;
	}
	rep(i,0,3) rep(j,0,3) g[i][j] = 1;
	LL ans = 0;
	dep(i,62,0){
		bool flag = false;
		rep(j,0,3) rep(k,0,3) {
			g1[j][k] = n + 2;
			rep(t,0,3) g1[j][k] = min(g[j][t] + f[i][t][k] - 1, g1[j][k]);
			if (g1[j][k] - 1 <= n) flag = true;
		}
		if (flag) {
			rep(j,0,3) rep(k,0,3) g[j][k] = g1[j][k];
			ans += 1LL << i;//LL!
		}
	}
	printf("%lld\n",ans);
}


bool check(long long x,long long n) {
    long long dp[4];
    for (int i = 0; i < 4; i++)
        dp[i] = 1;
    long long mn[4][4];
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
                mn[i][j] = c[i]->min[j];
    for (long long cur = 1; x > 0; cur <<= 1) {
        if (x & cur) {
            long long sw[4];
            for (int i = 0; i < 4; i++)
                sw[i] = OO;
            for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++)
                    sw[j] = min(sw[j],dp[i] + mn[i][j]);
            x -= cur;
            for (int i = 0; i < 4; i++)
                dp[i] = sw[i];
        }
        long long f[4][4];
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                f[i][j] = OO;
        for (int k = 0; k < 4; k++)
            for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++)
                    f[i][j] = min(f[i][j],mn[i][k] + mn[k][j]);
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                mn[i][j] = f[i][j];
    }
    for (int i = 0; i < 4; i++)
        if (dp[i] <= n)
            return 1;
    return 0;
}