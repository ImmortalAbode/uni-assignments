print('Введите значение |х|<∞ и n>=0 соответственно через пробел:')
x, n = (int(i) for i in input().split())
if n >= 0:
    s = 0
    for i in range(0, n+1):
        factorial = 1
        for j in range(1, 2*i+1):
            factorial = factorial*j
        s = s + (((-1)**i)*(x**(2*i)))/factorial
    print('Значение вашего выражения = ', s)
else:
    print('Вы ввели не удовлетворяющие условиям значение n')
