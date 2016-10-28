#include <cstdio>
#include <iostream>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
const int N = 500010;
char s[N];
int c[N], t[N], t1[N], sa[N], n;
void buildsa(){
	int *x = t, *y = t1;
	rep(i,0,25) c[i] = 0;
	rep(i,0,n - 1) c[x[i] = s[i] - 'a']++;
	rep(i,1,25) c[i] += c[i - 1];
	rep(i,0,n - 1) sa[--c[x[i]]] = i;
	int m = 26;
	for(int k = 1; k <= n; k <<= 1){
		int p = 0;
		rep(i, n - k, n - 1) y[p++] = i;
		rep(i, 0, n - 1) if (sa[i] >= k) y[p++] = sa[i] - k;

		rep(i, 0, m - 1) c[i] = 0;
		rep(i, 0, n - 1) c[x[y[i]]]++;
		rep(i, 1, m - 1) c[i] += c[i - 1];
		dep(i, n - 1, 0) sa[--c[x[y[i]]]] = y[i];

		swap(x,y);
		p = 1, x[sa[0]] = 0;
		rep(i, 1, n - 1)
			x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k]) ? p - 1 : p++;
		m = p;
		if (m >= n) break;
	}
}
int rank1[N], h[N];
void geth(){
	rep(i,0,n - 1) rank1[sa[i]] = i;
	int k = 0;
	rep(i,0,n - 1) if (rank1[i]){
		if (k) k--;
		while (sa[rank1[i] - 1] + k < n && i + k < n && s[i + k] == s[sa[rank1[i] - 1] + k]) k++;
		h[rank1[i]] = k;
	}
}
int Len[N], top = 0, ans = 0;
typedef pair<int, int> node;
#define len first
#define lcp second
#define mp(a,b) make_pair(a,b)
node q[N];
int main(){
	scanf("%s",s);n = strlen(s);
	buildsa();
	geth(); 
	rep(i,0,n - 1) Len[i] = n - sa[i];
	
	printf("%d\n",ans);
}