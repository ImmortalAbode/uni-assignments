def eratosthenes(n):
    a, b = [i for i in range(2, n+1)], []
    for p in a:
        if p > 1:
            for j in range(2*p-2, len(a), p):
                a[j] = 0
    for i in a:
        if i > 0:
            b.append(i)
    return b


print('Введите число n, до которого требуется выписать все простые числа:')
n = int(input())
if n >= 2:
    a, b = [i for i in range(1, n + 1)], []
    for i in a:
        if i % 7 == 0:
            b.append(i)
    print('a) Все числа от 1 до n, кратные 7:', b)
    print('б) Все простые числа от 1 до n: ', eratosthenes(n))
else:
    print('Введите натуральное число')
