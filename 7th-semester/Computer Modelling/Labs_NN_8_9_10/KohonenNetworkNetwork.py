# -*- coding: Windows-1251 -*-

import numpy as np
import matplotlib.pyplot as plt
import pickle
import os

from numpy.core.numeric import outer

# Функция для записи в файл.
def write_to_file(file_path, text):
    with open(file_path, 'a') as f:
        f.write(text + '\n')  
# Загружаем данные из файла.
def process_csv(file_path):
    headers = []
    subheaders = []
    data = []

    with open(file_path, 'r') as file:
        for i, line in enumerate(file):
            # Разделяем строку по запятым
            elements = line.strip().split(',')

            if i == 0:
                # Первая строка: записываем в headers
                headers = elements
            else:
                elements = line.strip().split(';')
                # Остальные строки
                subheaders.append(elements[0])  # Первый элемент добавляем в subheaders
                # Остальные элементы очищаем от пробелов и добавляем в data
                row_data = [elem.replace(' ', '') for elem in elements[1:]]
                data.append(row_data)

    return headers, subheaders, data

# Функция нормализации данных.
def normalize_data(data):
    data_array = np.array(data, dtype=float)
    data_transposed = data_array.T
    row_sums = np.sum(data_transposed, axis=1)
    normalized_data = data_transposed / row_sums[:, np.newaxis]
    normalized_data_transposed = normalized_data.T

    return normalized_data_transposed

# Инициализация сети Кохонена.
def initialize_network(grid_size, num_features):
    return np.random.rand(grid_size, grid_size, num_features)

# Вычисление расстояния между векторами.
def calculate_distance(input_vector, weight_vector):
    return np.linalg.norm(input_vector - weight_vector)

# Обновление весов нейронов относительно нейрона-победителя.
def update_weights(grid_size, weights, input_vector, winner_coords, learning_rate, neighborhood_radius):
    for x in range(grid_size):
        for y in range(grid_size):
            distance_to_winner = np.sqrt((x - winner_coords[0]) ** 2 + (y - winner_coords[1]) ** 2) # Вычисление Евклидова расстояния между нейроном и нейроном-победителем.
            if distance_to_winner <= neighborhood_radius:
                influence = np.exp( - (distance_to_winner ** 2) / (2 * (neighborhood_radius ** 2))) # Гауссиан, где distance_to_winner = Евклидову расстоянию (уже вычислено).
                weights[x, y] += influence * learning_rate * (input_vector - weights[x, y]) # Обновление весов с учетом функции Гауссиан, т.е. чем дальше нейроны от нейрона-победителя, тем меньше влияние.

# Обучение сети Кохонена.
def train_kohonen(data, grid_size, num_epochs, initial_learning_rate, initial_radius, output_file):
    num_features = data.shape[1] # Количество координат (синаптических весов) нейронов = числу столбцов (X) в исходных данных.
    # ШАГ 1. Инициализация сети.
    weights = initialize_network(grid_size, num_features)
    learning_rate = initial_learning_rate # Скорость обучения нейросети.
    radius = initial_radius # Радиус соседства нейрона-победителя.

    # Обучение нейросети по эпохам.
    for epoch in range(num_epochs):
        # ШАГ 2. Предъявление сети нового входного сигнала.
        for input_vector in data:
            # ШАГ 3. Вычисление расстояния до всех нейронов сети.
            distances = np.array(
                [[calculate_distance(input_vector, weights[x, y]) for y in range(grid_size)] for x in range(grid_size)]
            )
            # Шаг 4. Выбор нейрона с наименьшим расстоянием.
            winner_coords = np.unravel_index(np.argmin(distances), distances.shape) # np.agrmin - возвращает индекс мин. элемента независимо от формы;
                                                                                    # .shape - форму матрицы в виде кортежа (_;_);
                                                                                    # np.unreavel_index - преобразует индекс относительно формы матрицы, т.е. индекс 14 в матрице 10x10 вернет (1;5).
            # Шаг 5. Настраивание весов нейрона и его соседей.
            update_weights(grid_size, weights, input_vector, winner_coords, learning_rate, radius)

        # Уменьшаем скорость обучения ("ширину пакетов") и радиус влияния на соседей
        learning_rate *= 0.9
        radius *= 0.9
        # Шаг 6. Возвращаемся к шагу 2.

        if (epoch + 1) % 10 == 0:
            print(f"Сеть Кохонена прошла обучение на {epoch + 1}/{num_epochs} эпох.")
            write_to_file(output_file, f"Сеть Кохонена прошла обучение на {epoch + 1}/{num_epochs} эпох.")
    return weights

# Распределение данных по нейронам (кластеризация примеров).
def assign_data_to_neurons(data, weights, grid_size, output_file):
    # Создание словаря: ключ - коорд. нейрона, значение - индексы примеров.
    clusters = {(x, y): [] for x in range(grid_size) for y in range(grid_size)}

    # Итерация по исходной выборке.
    for idx, input_vector in enumerate(data):
        # Вычисление расстояний примера до каждого обученного нейрона.
        distances = np.array(
            [[calculate_distance(input_vector, weights[x, y]) for y in range(grid_size)] for x in range(grid_size)]
        )
        # Определение нейрона победителя.
        winner_coords = np.unravel_index(np.argmin(distances), distances.shape)
        # По координатам нейрона победителя заносится индекс примера.
        clusters[winner_coords].append(idx)

    # Вывод кластеров в консоль
    write_to_file(output_file, f"Нейроны были разделены на следующие кластеры:")
    for (x, y), indices in clusters.items():
        write_to_file(output_file, f"Нейрон ({x}, {y}) имеет следующие индексы примеров: {indices}")

    write_to_file(output_file, "")

    print(f"Входные данные были распределены по кластерам.")
    return clusters

# Визуализация карты с подписями.
def visualize_kohonen_with_labels(weights, clusters, region_names, grid_size, output_file):
    umatrix = np.zeros((grid_size, grid_size))

    # Вычисление U-матрицы (сходство между нейронами).
    for x in range(grid_size):
        for y in range(grid_size):
            neighbors = []
            if x > 0:
                neighbors.append(weights[x - 1, y])
            if x < grid_size - 1:
                neighbors.append(weights[x + 1, y])
            if y > 0:
                neighbors.append(weights[x, y - 1])
            if y < grid_size - 1:
                neighbors.append(weights[x, y + 1])
            umatrix[x, y] = np.mean([np.linalg.norm(weights[x, y] - neighbor) for neighbor in neighbors])
            write_to_file(output_file, f"Нейрон ({x},{y}): {umatrix[x,y]}")

    # Транспонирование матрицы umatrix для поворота картинки (корректное отображение по осям).
    umatrix = umatrix.T

    # Создание визуализации.
    plt.figure(figsize=(10, 8))
    plt.imshow(umatrix, cmap='coolwarm', interpolation='nearest', origin='lower')
    plt.colorbar(label="Cluster Similarity")
    plt.title("Self-Organizing Map with Region Labels")
    write_to_file(output_file, "Проверка подписей:")
    for (x, y), indices in clusters.items():
        if indices:
            label = ", ".join([region_names[idx] for idx in indices])[:10] + "..." if len(indices) > 1 else region_names[indices[0]][:10] + "..."
            plt.text(x, y, label, ha='center', va='center', fontsize=4, color='white', wrap=True)
            write_to_file(output_file, f"Нейрон ({x},{y}) содержит объекты: {', '.join([region_names[idx] for idx in indices])}")

    plt.xlabel("Neuron X")
    plt.ylabel("Neuron Y")
    plt.show()


# Сохранение обученной сети в файл.
def save_kohonen_network(weights, file_path):
    with open(file_path, 'wb') as file:
        pickle.dump(weights, file)

# Загрузка обученной сети из файла.
def load_kohonen_network(file_path):
    with open(file_path, 'rb') as file:
        return pickle.load(file)

# Основная функция
def main():
    # Чтение исходных данных.
    file_path = "Банковские_депозиты.txt"
    output_file = "output_log.txt"
    trained_model_path = "kohonen_network.pkl"

    # Очищаем файл перед записью.
    with open(output_file, 'w') as f:
        f.write('Training Log...\n\n')

    headers, subheaders, data = process_csv(file_path)

    # Нормализация данных.
    normalized_data = normalize_data(data)

    # Параметры сети Кохонена.
    grid_size = 10  # Размер карты нейронов (10x10).
    num_epochs = 100 # Число эпох обучения.
    initial_learning_rate = 0.5 # Начальная скорость обучения.
    initial_radius = 3 # Начальный радиус влияния нейрона-победителя на соседей.

    # Запрос пользователю.
    user_choice = input("Хотите использовать уже обученную модель (y/n [any symbols])? ").strip().lower()
    if user_choice == 'n':
        # Запись в файл.
        write_to_file(output_file, 'Исходные данные успешно загружены.')
        write_to_file(output_file, f'Размер обучающей выборки: {len(normalized_data[0])} примеров.')
        print("Обучение сети Кохонена...")
        write_to_file(output_file, "Обучение сети Кохонена...")
        weights = train_kohonen(normalized_data, grid_size, num_epochs, initial_learning_rate, initial_radius, output_file)
        # Сохранение обученной сети.
        save_kohonen_network(weights, trained_model_path)
        print("Обученная модель была сохранена в файл {trained_model_path}\n")
        write_to_file(output_file, f"Обученная модель была сохранена в файл {trained_model_path}\n")
    else:
        # Проверка наличия файла с обученной сетью.
        if not os.path.exists('kohonen_network.pkl'):
            print("Файл с обученной сетью не найден. Завершение программы.")
            return
        # Загрузка обученной сети.
        print("Загружаем обученную модель...")
        write_to_file(output_file, "Загружаем обученную модель...")
        weights = load_kohonen_network('kohonen_network.pkl')

    # Распределение данных по нейронам (кластеризация примеров).
    data_clusters = assign_data_to_neurons(normalized_data, weights, grid_size, output_file)

    # Визуализация карты с подписями для регионов.
    print("Визуализация карты Кохонена...")
    write_to_file(output_file, "Карта Кохонена была визуализирована!")
    region_names = subheaders
    visualize_kohonen_with_labels(weights, data_clusters, region_names, grid_size, output_file)

# Запуск программы
if __name__ == '__main__':
    main()
