from sys import *

a = int(stdin.readline())
b = int(stdin.readline())

if b-a > 180:
    print(b-a-360)
elif b-a > -180:
    print(b-a)
else:
    print(b-a+360)
