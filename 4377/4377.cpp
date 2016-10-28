#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
using namespace std;
const int N = 1000010;
char s[N];
typedef pair<int, int> node;
#define mp(a,b) make_pair(a,b)
int S[N * 4];
node a[N * 4]; int L = 0;
void add(int l, int r){ a[++L] = mp(l, 1); a[++L] = mp(r + 1, -1); }
int find(int x) { int l = 0, r = L + 1; while (l + 1 < r) { int mid = (l + r) >> 1; if (a[mid].first <= x) l = mid; else r = mid; } return l; }
int main(){
	int n; scanf("%d",&n); int A, b, p, m; scanf("%d%d%d%d",&A,&b,&p,&m); 
	scanf("%s",s + 1);
	int c = 0;
	rep(i,1,m){
		int l, r; //(x + c) \in [l,r]
		if (s[i] == '0') l = 0, r = p - 1;
		else l = p, r = n - 1;

		//x \in [l,r]
		l = (l - c + n) % n, r = (r - c + n) % n;
		if (l <= r) add(l, r);
		else add(l, n - 1), add(0, r);
		c += A, c %= n;
	}
	sort(a + 1, a + L + 1);
	int ans = 0;
	a[L + 1].first = n;
	rep(i,1,L){
		S[i] = S[i - 1] + a[i].second;
		if (S[i] == m) ans += a[i + 1].first - a[i].first;
	}

	rep(i,n - m + 1, n - 1){
		int c = (1LL * i * A % n + b) % n;
		if (S[find(c)] == m) ans--; 
	}

	printf("%d\n",ans); return 0;
}