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
const int mod = 1000000007, N = 2000010;
char s[N];
int T[N], p[N], vis[N];
int main(){
	scanf("%s",s + 1); int n = strlen(s + 1);
	dep(i,n,1) s[i << 1] = s[i];
	n = (n << 1) + 1;
	rep(i,1,n) if (i & 1) s[i] = '*';
	s[0] = '-', s[n + 1] = '+';
	int ans = 1;
	int mx = 0, j = 0, l = 0, cnt = 0;
	rep(i,1,n){
		if (i < mx) p[i] = min(p[2 * j - i], mx - i);
		else {
			p[i] = 1;
			if (i & 1) T[i] = 0;
			else {
				ans = 1LL * ans * (26 - cnt) % mod;
				T[i] = ++l;
			}
		}
		if (s[i - p[i]] == s[i + p[i]]) cnt = 0;
		while (s[i - p[i]] == s[i + p[i]]) {
			T[i + p[i]] = T[i - p[i]];
			p[i]++;
		}
		if (i + p[i] >= mx && vis[T[i - p[i]]] != i + p[i] && T[i - p[i]]) cnt++, vis[T[i - p[i]]] = i + p[i];
		if (i + p[i] > mx) mx = i + p[i], j = i;
	}
	cout <<ans<<endl;
}