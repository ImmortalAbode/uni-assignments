import threading


def func():
    i = 100
    while i >=0:
        print(i)
        i -= 1


t = threading.Thread(target=func)
t.start()