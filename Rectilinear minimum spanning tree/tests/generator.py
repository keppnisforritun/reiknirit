
import sys
import random

if len(sys.argv) < 2:
	print("argument n required: python generator.py n")
	sys.exit()

n = int(sys.argv[1])

print(n)

mincoord = -100
maxcoord = 100

if len(sys.argv) >= 4:
	mincoord = int(sys.argv[2])
	maxcoord = int(sys.argv[3])

if len(sys.argv) >= 5:
	random.seed(int(sys.argv[4]))

for i in range(0,n):
	print("{} {}".format(int((maxcoord - mincoord)*random.random() + mincoord),int((maxcoord - mincoord)*random.random() + mincoord)))






