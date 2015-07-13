from sys import*

def filltable(n):
	global table
	lis=[0 for i in range(n)]
	ind=0
	for i in range(1,n+1):
		for j in range(i):
			#print(i,j)
			ind=(ind+1)%n
			while lis[ind]>0:
				#print((ind,lis[ind]))
				ind=(ind+1)%n
		lis[ind]=i
		if i==n:
			break
		ind=(ind+1)%n
		while lis[ind]>0:
			ind=(ind+1)%n
	table[n]=[i for i in lis]
	#print(lis)

def printperm(li):
	for i in li:
		print(i,end=' ')
	print('')

table={i:[i]*i for i in range(1,14)}

for i in range(13):
	filltable(i+1)

N=int(stdin.readline())
for i in range(N):
	printperm(table[int(stdin.readline())])

