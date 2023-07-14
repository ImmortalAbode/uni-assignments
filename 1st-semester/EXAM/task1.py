import random


a = [random.randint(-10, 10) for i in range(10)]
pr = 1
for i in a:
    if a.index(i) % 2 == 0:
        pr = pr*i

print(a)
print(pr)
