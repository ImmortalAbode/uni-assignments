import random

print('Введите количество элементов списка, не менее 2:')
n = int(input())
if n < 2:
    print('Недостаточное количество элементов в списке')
else:
    a = []
    b = []
    count = 0
    for i in range(0, n):
        a.append(random.randint(-1000, 1000))
    print('Ваш список А:')
    print(a)
    for i in a:
        if i < 0:
            b.append(i)
    for i in a:
        if i >= 0:
            b.append(i)
    print('Ваш преобразованный список А:')
    print(b)
