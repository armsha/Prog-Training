from sys import *

N=int(stdin.readline())

for i in range(N):
	l=[int(i) for i in stdin.readline().split()]
	if l[0]<l[1]-l[2]:
		print("advertise")
	elif l[0]==l[1]-l[2]:
		print("does not matter")
	else:
		print("do not advertise")
		