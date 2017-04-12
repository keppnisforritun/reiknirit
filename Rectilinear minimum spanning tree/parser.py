#!/usr/bin/env python
import sys
import io

def parse(s):
    """
    Parses input for test cases and checks if input is starts with an integer
    n, and that there are following n lines of integers.
    """
    s = s.strip().split("\n")
    n = s[0]
    if not n.isdigit():
        return False
    n = int(n)
    c = 0
    for i in range(1, len(s)):
        uv = s[i].split()
        if not uv[0].isdigit or not uv[1].isdigit():
            return False
        u = int(uv[0])
        v = int(uv[1])
        c += 1
    if n != c:
        return False
    return True

if __name__ == "__main__":
    print(parse(sys.stdin.read()))
