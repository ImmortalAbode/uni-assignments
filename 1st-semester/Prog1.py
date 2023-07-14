print('Ваше уравнение = ', '|x-c|/(x+b)=(a-x)/(x+b)')
print('Введите значения a, b и c')
a, b, c = (float(i) for i in input().split())
if a == c:
    if -b < c:
        print('Ответ: с учётом ОДЗ',  '(-∞;', -b, ')', '(', -b, ';', c, ']')
    elif -b == c:
        print('Ответ: c учётом ОДЗ x<', c)
    else:
        print('Ответ: с учётом ОДЗ x<=', c)
else:
    if (c <= a) and ((a+c)/2 != -b):
        print('Ответ: с учётом ОДЗ', (a+c)/2)
    else:
        print('Ответ: корней нет')
