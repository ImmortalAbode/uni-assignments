print('Введите радиусы R1 и R2, R1>R2')
R1, R2 = (float(i) for i in input().split())
S1 = 3.14*(R1**2)
S2 = 3.14*(R2**2)
print('Площадь круга S1 = ', S1)
print('Площадь круга S2 = ', S2)
print('Площадь кольца S3 = ', S1-S2)