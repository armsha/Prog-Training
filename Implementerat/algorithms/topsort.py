
def topsort(G):
	N=len(G)
	roots=[]
	d=[0 for i in G]
	for i in range(N):
		for j in G[i]:
			d[j]+=1


	for i in range(N):
		if d[i]==0:
			roots.append(i)

	ind=0
	while len(roots)<N:
		#print(ind,roots)
		root=roots[ind]
		for i in G[root]:
			d[i]-=1
			if d[i]==0:
				roots.append(i)

		ind+=1

	return roots

Path=[[1],[2],[3],[]]
Gr=[[1,2],[3],[3,4],[4],[]]

print(topsort(Path))
print(topsort(Gr))

