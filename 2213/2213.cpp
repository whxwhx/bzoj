#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define max(a,b) ((a) > (b) ? (a) : (b))
#define rep(i,a,b) for(int i = a; i <= b; i++)
using namespace std;
const int N = 1000010;
char s[N];
int a[N], b[26], b1[26];
int main(){
	int n; scanf("%d",&n);
	scanf("%s",s + 1);
	rep(i,1,n) a[i] = s[i] - 'a';
	int ans = 0;
	rep(j,0,25){
		rep(i,0,25) b[i] = 0, b1[i] = -n;
		rep(i,1,n) if (a[i] == j){
			rep(k,0,25) if (k != j){
				b[k]--, b1[k] = b[k], ans = max(ans, b1[k]);
				if (b[k] < 0) b[k] = 0;
			}
		}else b[a[i]]++, b1[a[i]]++, ans = max(ans, b1[a[i]]); 
	}
	printf("%d\n",ans);
}