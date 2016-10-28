#include <iostream>
#include <cstdio> 
#include <algorithm>
using namespace std;
#define rep(i,a,b) for(int i=a;i<=b;i++)
const int N = 2 * 100000 + 10, M = 1007;
typedef pair<int, int> node;
#define mp(a,b) make_pair(a,b)
#define x first
#define y second
struct hash{
	int h[M][M], l, pre[N], s[N];
	node q[N];
	hash(){
		l = 0;
	}
	int ins(node a, int s1){
		for(int i = h[a.x % M][a.y % M]; i; i = pre[i]) 
			if (q[i] == a) return s[i];
		q[++l] = a, s[l] = s1;
		pre[l] = h[a.x % M][a.y % M], h[a.x % M][a.y % M] = l;
		return s1;
	}
}h;
int main(){
	int n; scanf("%d",&n);
	int J = 0, O = 0, I = 0, ans = 0;
	h.ins(mp(n,n),0);
	rep(i,1,n){
		char c = getchar();
		while (c != 'J' && c != 'O' && c != 'I') c = getchar();
		if (c == 'J') J++;
		if (c == 'O') O++;
		if (c == 'I') I++;
		int tmp = h.ins(mp(J - O + n, O - I + n), i);
		if (i - tmp > ans) ans = i - tmp;
	}
	printf("%d\n",ans);
}