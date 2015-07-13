
def inversion(A):
	n=len(A)
	if n<=1:
		return (A,0)
	left=A[:n//2]
	right=A[n//2:]
	count=0
	(left,l)=inversion(left)
	(right,r)=inversion(right)
	count+=l+r
	final=[]
	ind1=0
	ind2=0
	while ind1<len(left) and ind2<len(right):
		if left[ind1]<=right[ind2]:
			final.append(left[ind1])
			ind1+=1
		elif left[ind1]>right[ind2]:
			final.append(right[ind2])
			ind2+=1
			count+=(len(left)-ind1)

	if ind1<len(left):
		final+=left[ind1:]

	final+=right[ind2:]

	return(final,count)



A=[1,2,4,5,1,2,3,3]

print(inversion(A))
