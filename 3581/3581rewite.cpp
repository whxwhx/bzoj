#include <iostream>
#include <map>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
using namespace std;

typedef long long LL;
typedef unsigned int ui;
typedef pair<int, LL> node;
struct card{ int col, num; };

#define mp(a,b) make_pair(a,b)

map<LL, ui> T, H, T2;
map<node, ui> F;

const int N = 32;
int main(){
	int n; scanf("%d",&n);
	rep(i,1,n) scanf("%d%d",&a[i].col, &a[i].num);
	sort(a + 1, a + n + 1);
	
	int j = 1;
	rep(i,0,9){
		int t = j;
		while (j <= n && a[j].num == i) j++;
		if (t < j){
			T.clear();
			dfs(0, 0);

			
		}
	}
}