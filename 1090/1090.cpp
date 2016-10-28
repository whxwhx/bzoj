#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
char s[110];
int l, f[110][110], q[110];
bool c[110][110][110];
vector<int> d[110];
#define pb(a) push_back(a);
typedef vector<int>::iterator vit;
bool check(int a, int b, int c, int d){
	if (a + 1 < d) return 1;
	rep(i, 1, c) if (s[a + i] != s[b + i]) return 0;
	return 1;
}
int main(){
	scanf("%s",s + 1), l = strlen(s + 1);
	rep(i,1,100) rep(j,1,i) if (i % j == 0) d[i].pb(j);
	rep(i,1,9) q[i] = 1;
	rep(i,10,99) q[i] = 2;
	q[100] = 3;

	rep(i,1,l) {
		rep(j,1,l) c[i][i - 1][j] = 1;
		rep(j, i, l)
			for(vit t = d[j - i + 1].begin();t!=d[j - i + 1].end();t++)
				c[i][j][*t] = c[i][j - *t][*t] && check(j - *t - *t, j - *t, *t, i);
	}

	dep(i,l,1){
		f[i][i - 1] = 0;
		rep(j,i,l){
			f[i][j] = f[i][j - 1] + 1;
			rep(k,i,j - 1)
				for(vit t = d[j - k + 1].begin();t!=d[j - k + 1].end();t++)
					if (c[k][j][*t])
						f[i][j] = min(f[i][j], f[i][k - 1] + f[k][k + *t - 1] + 2 + q[(j - k + 1) / *t]);					
		}
	}
	printf("%d\n",f[1][l]);
	return 0;
}