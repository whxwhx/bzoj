n=1000
print n
import random
m=0
vis = [0 for x in range(1000000)]
for i in range(n):
	t = random.randint(1,4)
	if (t > 3) : t = 1
	if (t == 1):
		print t,random.randint(1,1000000),random.randint(1,1000000)
		m+=1
	if (t == 2):
		if (m == 0):
			t = 3;
		else :
			k = random.randint(1, m)
			while (vis[k] and k <= m):
				k+=1;
			if (k > m):
				t = 3
			else :
				print t,k;
				vis[k] = 1;
	if (t == 3):
		print t,random.randint(1,1000000),random.randint(1,1000000)
