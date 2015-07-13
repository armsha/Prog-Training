
def gcd(a,b):
	if a<b:
		return gcd(b,a)
	while b:
		(a,b)=(b,a%b)
	return a

print gcd( 3, 5 )
print gcd( 15, 5 )
print gcd( 25, 10 )
print gcd( 101, 991 )
print gcd( 1234, 534 )
print gcd( 12341234, 2134 )
print gcd( 123213, 213 )
print gcd( 4232, 3212 )


