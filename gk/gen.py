import random
print("create I 100 100")
print("pen color P 1 1 0")
n = 10000
print("fill I 0 0 0")
for _ in range(100):
    print("polygon I P {}".format(n))
    for x in range(n):
        print("{} {}".format(random.randint(0, 99), random.randint(0, 99)))

print("save I line.png")
print("exit 0")