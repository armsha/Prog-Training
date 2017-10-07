
#Computes K*r1+r2
def rAdd(r1,r2,K):
	return [r1[i]*K+r2[i] for i in range(len(r1))]

#Returns gcd(a,b),x,y s.t. ax+by=gcd(a,b)
def Blankinship(a,b):
	M=[[a,1,0],[b,0,1]]
	while M[0][0]>0 and M[1][0]>0:
		if M[0][0]>M[1][0]:
			K=M[0][0]//M[1][0]
			M[0]=rAdd(M[1],M[0],-K)
		else:
			K=M[1][0]//M[0][0]
			M[1]=rAdd(M[0],M[1],-K)
	if M[0][0]>0:
		return M[0]
	else:
		return M[1]

print(Blankinship(20,24))

