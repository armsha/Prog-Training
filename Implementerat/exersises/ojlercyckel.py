

def ojlercyckel( G ):

	if len(G) == 0:
		return None

	for x in range(len(G)):
		if len(G[x]) == 0:
			return None

	visEdg = [ [-1 for i in v] for v in G ]
	notDone = [ 0 for i in range(len(G)) ]
	for i,ii in enumerate(G):
		for j in ii:
			notDone[i] += 1
			notDone[j] += 1

	inc = [ 0 for i in range(len(G)) ]
	otg = [ 0 for i in range(len(G)) ]
	for i,ii in enumerate(G):
		for j in ii:
			inc[j] += 1
			otg[i] += 1


	# print( inc, otg )
	# print( notDone )
	if not otg == inc:
		return None


	for x in notDone:
		if x%2 != 0:
			return None		

	k = 0
	e = None

	l = []
	while True:

		# print( "A" )
		# print( visEdg )
		# print( notDone )

		s = -1
		for i,x in enumerate(notDone):
			# print( i, x )
			if not x == 0:
				s = i
				break
		if s == -1:
			break

		t = []
		kk = 0

		for i in range(len(G[s])):
			if visEdg[s][i] == -1:
				e = G[s][i]
				visEdg[s][i] = k
				k += 1

				if i == 0:
					kk = k
				else:
					kk = visEdg[s][i-1]+2

				notDone[s] -= 2
				# print( "e", i, e )
				break
		ss = s

		t.append( (s,e) )
		while ss != e:
			# print( s )
			s = e
			# print(s,G) 
			# print(visEdg)
			# print(notDone)
			for i in range(len(G[s])):
				if visEdg[s][i] == -1:
					e = G[s][i]
					visEdg[s][i] = k
					k += 1
					notDone[s] -= 2
					t.append( (s,e) )
					break
			
		print(t)
		print(kk,l)
		print(visEdg)
		print()
		l = l[:kk]+t+l[kk:]

	return l



G1 = [[1,2,3,4],[0,2],[3,4],[5,1],[1,2,3,5],[3,4]]
G2 = [[3,4,5],[0,2],[0,3,4],[0,1],[2,4,5],[2,1,5]]
print( ojlercyckel(G1) )
print( ojlercyckel(G2) )

