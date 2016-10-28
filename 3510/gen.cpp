#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
using namespace std;
int f[100010];
pair<int, int> e[100010];
int main(){
	int t; cin >>t; srand(t);
	int n = 10, m = (n - 1) * 2;
	cout <<n<<' '<<m<<endl;
	rep(i,2,n) f[i] = rand() % (i - 1) + 1, e[i - 1] = make_pair(f[i], i);
	rep(i,1,n - 1) swap(e[i], e[rand() % i + 1]);
	rep(i,1,n - 1) cout <<'A'<<' '<<e[i].first<<' '<<e[i].second<<endl,
				   cout <<'Q'<<' '<<e[i].first<<endl;
}