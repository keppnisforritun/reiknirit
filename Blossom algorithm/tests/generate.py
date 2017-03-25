from sys import argv
from random import randint

graphtype = argv[1]

if graphtype == "complete":
    n = int(argv[2])
    print(n, n*(n-1)//2)
    for i in range(n):
        for j in range(i+1,n):
            print(i,j)
elif graphtype == "complete-bipartite":
    n, m = map(int, argv[2:4])
    print(n+m, m*n)
    for i in range(n):
        for j in range(n,n+m):
            print(i,j)
elif graphtype == "random":
    n = randint(0, int(argv[2]))
    k = randint(0, n*(n-1)//2)
    print(n,k)
    E = set()
    while len(E) < k:
        a = randint(0,n-1)
        b = randint(0,n-1)
        if a == b:
            continue
        if a > b:
            a,b = b,a
        E.add((a,b))
    for a,b in E:
        print(a,b)
elif graphtype == "random-bipartite":
    n, m = randint(1, int(argv[2])), randint(1, int(argv[3]))
    k = randint(0,n * m)
    print(n+m,k)
    E = set()
    while len(E) < k:
        a = randint(0,n-1)
        b = randint(n,n+m-1)
        E.add((a,b))
    for a,b in E:
        print(a,b)

