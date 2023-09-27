import sys

def gcd(a, b):
    if a == 0: return b
    if b == 0: return a
    r = a % b
    while r != 0:
        a = b
        b = r
        r = a % b
    return b

if len(sys.argv) != 3 :
    sys.exit('Usage: %s <integer> <integer>' % sys.argv[0])

a = abs(int(sys.argv[1]))  # like abs(atoi(argv[1]))
b = abs(int(sys.argv[2]))  # like abs(atoi(argv[2]))

print(f"GCD({a}, {b}) = {gcd(a,b)}")