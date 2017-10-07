
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

#Inverse of k in Z_n
def modInverse(k,n):
	a=Blankinship(k%n,n)
	return a[1]

#Solves kx+n=c (mod m)
def Update(linear,constant,righthandside,modulus):
	HL=(righthandside-constant)%modulus
	HL*=modInverse(linear,modulus)
	HL%=modulus
	return((linear*modulus,constant+HL*linear))

#Assuming only prime moduli
def Solve(system):
	linear=1
	constant=0
	print(linear,constant)
	for congruence in system:
		(linear,constant)=Update(linear,constant,congruence[0],congruence[1])
		print(linear,constant)
	return constant


#Represent the congruences x=c_i mod m_i as a list of [c_i,m_i]
system=[[2,3],
        [3,5],
        [1,7]]

ans=Solve(system)
print(ans)

