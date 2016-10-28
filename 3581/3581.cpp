#include <iostream>
#include <cstdio>
#include <map>
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
typedef unsigned ui;
const int N = 31;
struct card{
	int col, num;
}a1[N];
bool operator < (const card &a, const card &b){
	return a.num < b.num;
}

int cnt[4];

int a[9];
LL calc_S(){
	LL S = 0;
	rep(i,0,8) S = S * 31 + a[i];
	return S;
}

map<LL, ui> H, T, T2;

ui c[10][10];
#define id(a,b) (a * 3 + b)
#define min(a,b) ((a) < (b) ? (a) : (b))
typedef map<LL, ui>::iterator MIT;

ui f[3][3][10][10][10];
struct edge{
	int s, t, r[3];
	ui ways;
}F;
int fl;

int r[3];
void dfs(int s, int t){
	f[s][t][r[0]][r[1]][r[2]]++;
	rep(i,0,2) if (i != t && cnt[i] < r[i]){
		r[i]++;
		dfs(s, i);
		r[i]--;
	}
}

void Dfs(int x, ui ways){
	if (x <= fl){
		dfs(x + 1, ways);
		rep(j,1,9){
			rep(i,0,2) r[i] += j * F[x].r[i]; ways *= F[x].ways;
			rep(i,0,2) if (cnt[i] < r[i]) {
				rep(k,0,2) r[i] -= j * F[x].r[i];
				return;
			}
			Dfs(x + 1, ways);
			rep(i,0,2) r[i] -= j * F[x];
		}
	}else{

	}
}

ui fac[10];
void work(){
	rep(i,0,2) rep(j,0,2) rep(k,0,cnt[0]) rep(t,0,cnt[1]) rep(g,0,cnt[2])
		f[i][j][k][t][g] = 0;

	rep(i,0,2) rep(j,0,2) if (i != j && cnt[i] && cnt[j]){
		r[0] = r[1] = r[2] = 0;
		r[i] = r[j] = 1;
		dfs(i, j, 1);
	}

	fl = 0;
	rep(i,0,2) rep(j,0,2) rep(k,0,cnt[0]) rep(t,0,cnt[1]) rep(g,0,cnt[2])
	if (f[i][j][k][t][g]) {
		fl++;
		F[fl].s = i, F[fl].t = j;
		F[fl].r[0] = k, F[fl].r[1] = t, F[fl].r[2] = g;
		F[fl].ways = f[i][j][k][t][g];
	}

	rep(i,0,2) r[i] = 0;
	Dfs(1, 1);
}

void merge(){
	T2.clear();
	for (MIT i = H.begin(); i != H.end(); i++){
		for(MIT j = T.begin(); j != T.end(); j++){
			LL S = i->first + j->first;
			MIT t = T2.find(S);
			if (t != T2.end()) t->second += i->second * j->second; 
			else T2[S] = i->second * j->second;
		}
	}
	H = T2;
}

map<pair<int, LL>, ui> f; 
typedef map<pair<int, LL>, ui>::iterator mit;

void decode(LL S){
	dep(i,8,0) a[i] = S % 31, S /= 31;
}
ui dp(int x, LL s){
	if (s == 0) return 1;
	mit t;
	if ((t = f.find(mp(x, s))) != f.end()) return (*t).second;
	ui ans = 0;
	rep(i,0,2) if (a[id(x,i)]){
		a[id(x,i)]--;
		ans += dp(i, calc_S()) * (a[id(x, i)] + 1);
		a[id(x,i)]++;
	}
	return (f[mp(x, s)] = ans);
}

int main(){
	int n; scanf("%d",&n);
	if (n == 0) {cout <<1<<endl; return 0;}
	rep(i,1,n) scanf("%d%d",&a1[i].col,&a1[i].num);
	sort(a1 + 1, a1 + n + 1);
	
	c[0][0] = 1;
	rep(i,1,9) {
		c[i][0] = c[i][i] = 1;
		rep(j,1,i - 1) c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
	}
	fac[0] = 1;
	rep(i,1,9) fac[i] = fac[i - 1] * i;
	int j = 1;
	//H.ins(0,1);
	H[0] = 1;
	
	rep(i,0,9){
		int t = j;
		while (j <= n && a1[j].num == i) j++;
		
		if (t < j){
			cnt[0] = cnt[1] = cnt[2] = 0;
			int tmp;
			rep(k,t,j - 1) cnt[a1[k].col]++, tmp = a1[k].col;
				
			rep(i,0,8) a[i] = 0;
			T.clear();//Tl = 0;
			
			work();

			merge();
		}
	}

	ui ans = 0;
	for(MIT i = H.begin(); i != H.end(); i++){
		LL S = i->first;
		decode(S);
		ans += (dp(1, S) + dp(2, S) + dp(0, S)) * i->second;
	}
	
	printf("%u\n",ans);
	return 0;
}