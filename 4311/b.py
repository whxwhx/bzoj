n=input();
m=0
x=[]
y=[]
vis=[]
for i in range(n):
	op = map(int, raw_input().split());
	if (op[0] == 1):
		m+=1
		x.append(op[1])
		y.append(op[2])
		vis.append(0)
	if (op[0] == 2):
		vis[op[1] - 1] = 1
	if (op[0] == 3):
		ans = 0
		for i in range(m):
			if (vis[i] == 0):
				if (op[1] * x[i] + op[2] * y[i] > ans) :
					ans = op[1] * x[i] + op[2] * y[i]
		print ans;
