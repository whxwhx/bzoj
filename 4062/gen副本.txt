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
void work(){
	int n = 100000, k = 500; cout <<n<<' '<<k<<endl;
	rep(i,1,n) cout <<rand() % 1000000 + 1<<' '<<rand() % 1000000 + 1<<' '<<rand() % k + 1<<endl;
}
int main(){
	int t; cin >>t; srand(t);
	cout <<10<<endl;
	rep(i,1,10) work();
}