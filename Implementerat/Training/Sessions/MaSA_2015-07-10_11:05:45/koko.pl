
r(a,b).

f(X,Y):-
	X<10,
	X>(-1),
	Y<10,
	X<Y.

fact(A,B):-
	A>0,
	Ax is A-1,
	fact(Ax,Bx),
	B is A*Bx.