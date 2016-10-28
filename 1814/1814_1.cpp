//最小表示法
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
	int head[M], pre[S], l;
	LL sta[S], f[S];
	inline void clr(){
		l = 0;
		memset(head,0,sizeof(head));
	}
	inline void ins(LL s, LL ans){
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
inline void decode(LL s){
	//cout <<s<<endl;
	t = 0;
	rep(i,0,m){
		ch[i] = s & 7, t = max(t, ch[i]);
		s >>= 3;
	}
}
inline LL encode(){
	LL s = 0;
	dep(i,m,0) {
		s <<= 3, s += ch[i];
		//if (ch[i] > 7) cout <<"hhhhh"<<endl;
	}
	//cout <<s<<endl;
	return s;
}
inline void dp(int i, int j){
	for(int k = 1; k <= h[!cur].l; k++){
		LL s = h[!cur].sta[k], f = h[!cur].f[k];
		//cout <<i<<' '<<j<<' '<<s<<' '<<f<<endl;
		decode(s);
		if (ch[j - 1] == 0 && ch[j] == 0){
			//if (t + 1 > 15) cout <<"!!!!"<<endl;
			if (!a[i][j + 1] && !a[i + 1][j]){
				ch[j - 1] = ch[j] = t + 1;
				h[cur].ins(encode(), f);
			}
		}else if (ch[j - 1] == 0 || ch[j] == 0){
			h[cur].ins(encode(), f);
			swap(ch[j - 1], ch[j]);
			h[cur].ins(encode(), f);
		}else if (ch[j - 1] != ch[j] || (i == ei && j == ej)){
			int tmp = min(ch[j - 1], ch[j]), tmp1 = max(ch[j - 1], ch[j]);
			ch[j - 1] = ch[j] = 0;
			rep(i,0,m) 
				if (ch[i] > tmp1) ch[i]--;
				else if (ch[i] == tmp1) ch[i] = tmp;
			h[cur].ins(encode(), f);
		}
	}
}
inline void dp_b(int i, int j){
	for(int k = 1; k <= h[!cur].l; k++){
		LL s = h[!cur].sta[k], f = h[!cur].f[k];
		if ((s >> (j - 1) & 63) == 0) h[cur].ins(s, f);
	}
}
inline void shift(){
	cur ^= 1;h[cur].clr();
	for(int i = 1; i <= h[!cur].l; i++){
		LL s = h[!cur].sta[i], f = h[!cur].f[i];
		if (s >> (m * 3) == 0) h[cur].ins(s << 3, f);
	}
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
	cur = 0;h[cur].clr();
	h[cur].ins(0,1);
	rep(i,1,n){
		rep(j,1,m){
			cur ^= 1, h[cur].clr();		
			if (i == n && j == m) flag = 1;	
			if (a[i][j]) dp_b(i,j); else dp(i,j);
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