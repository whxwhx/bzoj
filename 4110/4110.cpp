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
const int N = 4010;

struct node{
	char s[N];
	int len;
}T[N], s;
bool operator < (const node &a, const node &b){
	return a.len > b.len;
}

bool jud(const node &a, const node &b){ //a->b (b is a sub-squence of a)
	int j = 1;
	rep(i,1,a.len)
		if (a.s[i] == b.s[j]){
			j++;
			if (j > b.len) return true;
		}
	return false;
}

int cnt[2], ans[N][2];

int main(){
	int n; scanf("%d",&n);
	scanf("%s",s.s + 1);
	s.len = strlen(s.s + 1);
	rep(i,1,n){
		scanf("%s",T[i].s + 1);
		T[i].len = strlen(T[i].s + 1);
		if (!jud(s, T[i])) {printf("impossible\n");return 0;}
	}
	sort(T + 1, T + n + 1);
	T[0] = s;
	int t = 0, i = 1;
	while (i <= n){
		int j = i;
		while (jud(T[j], T[j + 1])) j++;
		if (j == n || jud(T[i - 1], T[j + 1])){
			rep(k,i,j) ans[++cnt[t]][t] = k;
			t ^= 1; 
		}else{
			int k = i;
			while (k <= j && !jud(T[i - 1], T[k])) k++;
			if (k <= j && jud(T[k - 1], T[j + 1])){
				rep(w,i,k - 1) ans[++cnt[t]][t] = w;
				t ^= 1;
				rep(w,k,j) ans[++cnt[t]][t] = w;
				t ^= 1;
			}else {printf("impossible\n");return 0;}
		}
		i = j + 1;
	}
	printf("%d %d\n", cnt[0], cnt[1]);
	
	dep(i,cnt[0],1) printf("%s\n",T[ans[i][0]].s + 1);
	dep(i,cnt[1],1) printf("%s\n",T[ans[i][1]].s + 1);

	return 0;
}