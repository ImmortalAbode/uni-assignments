import threading
import time
from string import ascii_letters  # Для создания случайной строки
import random  # Для случайного числа знаков в строке


# Функция генерации произвольных строк
def random_generation_string():
    while True:
        string = ''.join(random.choice(ascii_letters) for _ in range(random.randint(1, 100)))
        list_text.append(string)
        if len(list_text) > 100000:
            main_stream.daemon = True
            break


# Функция вывода текущего состояния списка на экран
def current_state_list_text():
    print('Текущее состояние списка:')
    print()
    while True:
        print(list_text)
        print()
        if len(list_text) > 100000:
            current_state_stream.daemon = True
            break


# Функция сортировки списка в алфавитном и порядке и сортировка списка раз в 5 секунд с сохранением в файл
def list_sorted_writer():
    while True:
        time.sleep(5)
        f = open('list_file.txt', 'w')
        list_text.sort()
        for one_string in list_text:
            f.write(one_string + '\n')
        f.close()
        if len(list_text) > 100000:
            sort_writer_stream.daemon = True
            break


# Начальное состояние списка
list_text = []


# Задание главного потока и двух дочерних потоков
main_stream = threading.Thread(target=random_generation_string)
current_state_stream = threading.Thread(target=current_state_list_text)
sort_writer_stream = threading.Thread(target=list_sorted_writer)

# Начало работы заданных потоков
main_stream.start()
current_state_stream.start()
sort_writer_stream.start()
