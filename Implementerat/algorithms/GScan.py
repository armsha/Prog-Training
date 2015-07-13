from math import *

def compfunc(a,b):
	global besteP
	#print a, b, atan2(a[1]-besteP[1],a[0]-besteP[0])<=atan2(b[1]-besteP[1],b[0]-besteP[0])
	if atan2(a[1]-besteP[1],a[0]-besteP[0])>=atan2(b[1]-besteP[1],b[0]-besteP[0]):
		return -1
	return 1
	#return atan2(a[1]-besteP[1],a[0]-besteP[0])>=atan2(b[1]-besteP[1],b[0]-besteP[0])

def turnswrong(p1,p2,p3):
	crossp=(p2[0]-p1[0])*(p3[1]-p1[1])-(p2[1]-p1[1])*(p3[0]-p1[0])
	print (p2[0]-p1[0])*(p3[1]-p1[1])-(p2[1]-p1[1])*(p3[0]-p1[0])
	return crossp<0

def GScan(P):
	global besteP
	besteP=P[0]

	for p in P:
		if P[0]==besteP[0]:
			if p[1]<besteP[1]:
				besteP=p
		if p[0]<besteP[0]:
			besteP=p
	print [i for i in P if i is not besteP]
	Ps=[besteP]+sorted([i for i in P if i is not besteP],cmp=compfunc)
	print(Ps)
	stack=Ps[:2]
	ind=2
	while ind<len(Ps):

		if len(stack)<2:
			stack.append(Ps[ind])
		else:
			while turnswrong(stack[-1],stack[-2],Ps[ind]) and len(stack)>2:
				del(stack[-1])
			
			stack.append(Ps[ind])

		ind+=1

	return stack




besteP=0
P=[(0,0),(0,1),(1,1),(1,0),(0.5,0.5)]
print(GScan(P))


P=[(0,0),(0,1),(1,1),(0.5,2),(1,0),(0.5,0.5),(2,0),(0.25, 2)]
print(GScan(P))

for i in P:
	for j in P:
		a=0#print(compfunc(i,j))
