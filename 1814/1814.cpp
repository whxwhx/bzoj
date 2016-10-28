//括号表示法
//by:whx
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
typedef long long LL;
using namespace std;
const int N = 12, M = 100007, S = 1000000;
bool flag = 0;
struct hash{
	int head[M], pre[S], l， sta[S];
	LL f[S];
	inline void clr(){
		l = 0;
		memset(head,0,sizeof(head));
	}
	inline void ins(int s, LL ans){
		int t = s % M;	
		for (int i = head[t]; i; i = pre[i])
			if (sta[i] == s) {
				f[i] += ans;
				return;
			}
		l++;//if (l >= S) cout <<"!!!"<<endl;
		sta[l] = s, f[l] = ans;
		pre[l] = head[t], head[t] = l;		
	}
}h[2];
int a[N + 5][N + 5], n , m, cur, ei = 0, ej = 0, ch[N + 4], t;
inline int findl(int s, int j){
	j = 1 << ((j - 1) * 2);
	for (;j;j >>= 2) if (s & j == j) return j;
}
inline int findr(int s, int j){
	j = 2 << ((j + 1) * 2);
	for (;j <= s;j <<= 2) if (s & j == j) return j;
}

inline void dp(int i, int j){
	rep(k,1,h[!cur].l){
		int s = h[!cur].s[k]; LL f = h[!cur].f[k];
		int left = s >> ((j - 1) * 2) & 3, up = s >> (j * 2) & 3;
		if ( left == 0 && up == 0 ){
			if (!a[i + 1][j] && !a[i][j + 1])
				h[cur].ins(s | ((2 << 2) + 1) << ((j-1) * 2), f);
		}else if (up == 0){
			if (!a[i + 1][j])
				h[cur].ins(s, f);
			if (!a[i][j + 1])
				h[cur].ins(s | ((left << 2) + left) << ((j - 1) * 2), f);
		}else if (left == 0){
			if(!a[i][j + 1])
				h[cur].ins(s,f);
			if (!a[i + 1][j])
				h[cur].ins(s | ((up << 2) + up) << ((j - 1) * 2), f);
		}else if (left != 1 || up != 2){
			if (left == 1){//up=2
				
			}
			if (left == 2){
				if (up == 1){

				}else{//up = 2

				}
			}
		}else if (i == ei && j == ej){
			
		}
	}
}
inline void shift(){

}
void work(){
	ei = ej = 0;
	rep(i,1,n) 
		rep(j,1,m){
			char c = getchar();
			while (c != '*' && c != '.') c = getchar();
			if (c == '.') 
				a[i][j] = 0, ei = i, ej = j;
			else 
				a[i][j] = 1;
		}
	if (ei == 0){
		printf("0\n");
		return;
	}
	rep(i,1,n) a[i][0] = a[i][m + 1] = 1;
	rep(i,1,m) a[0][i] = a[n + 1][i] = 1;
	cur = 0;h[cur].clr();
	h[cur].ins(0,1);
	rep(i,1,n){
		rep(j,1,m){
			cur ^= 1, h[cur].clr();		
			if (i == n && j == m) flag = 1;	
			if (!a[i][j]) dp(i,j);
		}
		shift();
	}
	LL ans = 0;
	for(int i = 1; i <= h[cur].l; i++) if (h[cur].sta[i] == 0) ans += h[cur].f[i];
	printf("%lld\n",ans);
}
int main(){
	while (scanf("%d%d",&n,&m) == 2) work();
	return 0;
}