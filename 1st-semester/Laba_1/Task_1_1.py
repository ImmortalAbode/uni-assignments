print('Введите два катета прямоугольного треугольника')
a, b = (float(i) for i in input().split())
c = (a**2+b**2)**0.5
P = a+b+c
print('Гипотенуза с = ', c)
print('Периметр P = ', P)
