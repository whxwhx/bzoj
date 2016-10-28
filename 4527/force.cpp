#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
using namespace std;
const int N = 10010;
int a[N], b[N];
int n, k, d; 
bool check(int l, int r){
	rep(i,l,r) b[i] = a[i]; sort(b + l, b + r + 1);
	int t = b[l], tk = k;
	rep(i,l + 1,r){
		if (b[i] == t) return false;
		while (t + d < b[i]) t += d, tk--;
		if (t + d != b[i] || tk < 0) return false;
		t = b[i];
	}
	return true;
}
int main(){
	scanf("%d%d%d",&n,&k,&d);
	rep(i,1,n) cin >>a[i];
	int ans = 1, ansx = 1;
	rep(i,1,n)
		rep(j,i+1,n)
			if (check(i,j)){
				if (j - i + 1 > ans || (j - i + 1 == ans && i < ansx)) ans = j - i + 1, ansx = i;
			}
	cout <<ansx<<' '<<ansx + ans - 1<<endl;
	return 0;
}