import random

print('Введите количество элементов списка, не менее 2:')
n = int(input())
if n >= 2:
    a = []
    b = []
    for i in range(0, n):
        a.append(random.randint(-1000, 1000))
    print('Ваш список А:')
    print(a)
    m = min(a)
    print('Минимальный элемент вашего списка = ', m)
    ind = a.index(m)
    for i in range(0, len(a)):
        if (a[i] > 0) or (i >= ind):
            b.append(a[i])
    print('Ваш преобразованный список А:')
    print(b)
else:
    print('Недостаточное количество элементов списка')

