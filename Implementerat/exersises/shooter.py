from sys import*

def changes(a,b):
	#printlist(a)
	#printlist(b)
	for i in range(len(a)):
		if abs(a[i]-b[i])>0.001:
			return True
	return False

def solve(lis,N):
	survival=[1.0 for i in lis]
	lis=[i/100 for i in lis]
	next=[i for i in survival]
	flag=0
	ind=0
	bestind=0
	while changes(survival,next) or flag==0:
		next[bestind]=survival[bestind]
		flag=1
		best=-1
		bestind=-1
		for i in range(N):
			if i!=ind:
				if survival[i]*lis[i]>best:
					best=survival[i]*lis[i]
					bestind=i
		#print(bestind)
		survival[bestind]*=(1-survival[ind]*lis[ind])
		ind=(ind+1)%N
		printlist(survival)

def printlist(l):
	for i in l:
			print(i,end=" ")
	print("")

N=int(stdin.readline())
for i in range(N):
	l=[int(i) for i in stdin.readline().split()]
	solve(l[1:],l[0])
