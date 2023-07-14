def func(number):
    if number == 1:
        return 1
    else:
        return number - func(func(number - 1))


n = int(input('Введите число n членов последовательности: '))
if n <= 0:
    print('Число членов последовательности должно быть n>0')
else:
    print('Искомые члены последовательности:')
    for i in range(1, n+1):
        print(func(i), end=' ')
