f = open("input.txt", "r")
num = int(f.read())
f.close()


def factorial(n):
    if n <= 1:
        return 1
    else:
        return n*factorial(n-1)


print(factorial(num))
