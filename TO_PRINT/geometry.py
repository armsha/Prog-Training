from math import *

def sw(a,b):
    return (a[0]<=b[0]) and (a[1]<=b[1])

def angle(x,p):
    return atan2(x[1]-p[1],x[0]-p[0])

def det(a,b):
    return a[0]*b[1]-b[0]*a[1]

def minus(a,b):
    return (a[0]-b[0],a[1]-b[1])

def right_turn(prev,curr,nextp):
    return det(minus(curr,prev),minus(nextp,curr)) > 0

def left_turn(prev,curr,nextp):
    return det(minus(curr,prev),minus(nextp,curr)) < 0

def graham_scan(poly):
    if len(poly) <= 3:
        return [i for i in poly]

    # Find SW point
    p=poly[0]
    ind=0
    count=0
    for q in poly[1:]:
        count+=1
        if sw(q,p):
            p=q
            ind=count


    print(p)

    poly = poly[:ind] + poly[ind+1:]

    # Sort
    poly.sort(key = lambda x: angle(x,p))

    # Run
    stack=[p,poly[0]]
    for q in poly[1:]:
        if len(stack)<2:
            stack.append(q)
            continue
        
        if right_turn(stack[-2],stack[-1],q):
            stack.append(q)
        elif left_turn(stack[-2],stack[-1],q):
            while len(stack)>=2 and left_turn(stack[-2],stack[-1],q):
                del(stack[-1])
            stack.append(q)

    return stack


poly = [(2/3,1),(0,1/2),(0,0),(1,1),(0.5,0.5),(1,0),(0,1)]

print(graham_scan(poly))

