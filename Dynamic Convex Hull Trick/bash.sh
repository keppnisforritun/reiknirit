g++ -Wall -O2 fast.cpp -o fast
g++ -Wall -O2 slow.cpp -o slow

while [ 1 ]; do
	python2 ./gen.py > input
	./slow < input > answer
	./fast < input > output
	diff output answer || break
done
