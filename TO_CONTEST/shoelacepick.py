
def gcd(a,b):
	if a<b:
		return gcd(b,a)
	while b:
		(a,b)=(b,a%b)
	return a

#Computes unsigned area of polygon
def shoelace(polygon):
	if len(polygon)<3:
		return 0
	ans=0
	N=len(polygon)
	for i in range(N-1):
		ans+=polygon[i][0]*polygon[i+1][1]-polygon[i][1]*polygon[i+1][0]
	ans+=polygon[N-1][0]*polygon[0][1]-polygon[N-1][1]*polygon[0][0]
	return ans/2

#Computes number of interior points via Pick's theorem
def Pick(polygon):
	area=shoelace(polygon)
	boundary=0
	
	for i in range(len(polygon)-1):
		boundary+=gcd(abs(polygon[i+1][0]-polygon[i][0]),abs(polygon[i+1][1]-polygon[i][1]))
	
	boundary+=gcd(abs(polygon[len(polygon)-1][0]-polygon[0][0]),abs(polygon[len(polygon)-1][1]-polygon[0][1]))
	
	print("Boundary =",boundary)
	return(area-boundary/2+1)

polygon=[[0,0],
         [4,0],
         [0,4],
         [-4,1],
         [0,-2]]

print(shoelace(polygon))
print(Pick(polygon))

polygon2=[[0,0],
         [3,3],
         [3,5],
         [-1,3]]

print(shoelace(polygon2))
print(Pick(polygon2))

polygon3=[[0,0],
         [1,0],
         [0,1]]

print(shoelace(polygon3))
print(Pick(polygon3))



