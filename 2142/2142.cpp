#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
int w[6], p[32], c[32], l = 0;
void factor(int n){
	for(int i = 2; i * i <= n; i++) if (n % i == 0){
		p[++l] = i;
		while (n % i == 0) c[l]++, n /= i;
	}
}
int main(){
	int p; scanf("%d",&p);
	int n, m; scanf("%d%d",&n,&m);
	factor(n);
	rep(i,1,m) scanf("%d",&w[i]);
	
}