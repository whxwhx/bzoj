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
int rev[20000];
typedef pair<int, int> node;
node a[20000];
int main(){
	srand(233);
	cout <<1<<endl;
	int n = 10000; cout <<n<<endl;
	rep(i,1,n) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << 20);
	rep(i,1,n) a[i] = mp(rev[i], i);
	sort(a + 1, a + n + 1);
	rep(i,1,n) cout <<a[i].second<<' ';
	cout <<endl;
}