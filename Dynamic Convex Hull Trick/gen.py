from random import randint
from random import uniform
n = randint(1,1000)
print(n)
for x in range(n):
    op = randint(1,2)
    if x == 0:
        op = 1
    if op == 1:
        a = uniform(-1000,1000)
        b = uniform(-1000,1000)
        print(str(op) + " " + str(a) + " " + str(b))
    else:
        x = uniform(-1000,1000)
        print(str(op) + " " + str(x))

