# -*- coding: Windows-1251 -*-
import numpy as np
import pickle
import os

# Загрузка данных из текстового файла.
def load_data(file_path):
    with open(file_path, 'r', encoding='Windows-1251') as file:
        lines = file.readlines()
    
    # Удаляем символы новой строки и разделяем строки на элементы.
    data = [line.strip().split(',') for line in lines]
    
    # Преобразуем строки в числа, где это необходимо.
    for i in range(1, len(data)):
        data[i] = [float(x) for x in data[i]]
    
    return data
# Функция сохранения нейросети на текущем наборе исходных данных.
def save_neural_network(file_path, input_hidden_weights, hidden_output_weights, hidden_bias, output_bias, output_file):
    model_data = {
        "input_hidden_weights": input_hidden_weights,
        "hidden_output_weights": hidden_output_weights,
        "hidden_bias": hidden_bias,
        "output_bias": output_bias
    }
    with open(file_path, 'wb') as file:
        pickle.dump(model_data, file)
    write_to_file(output_file, f"Параметры обученной нейросети сохранены в файл: {file_path}.\n\n") 
# Функция для записи в файл.
def write_to_file(file_path, text):
    with open(file_path, 'a') as f:
        f.write(text + '\n')  
# Функция для загрузки сохраненной модели.
def load_trained_model(file_path):
    if os.path.exists(file_path):
        with open(file_path, 'rb') as file:
            model_data = pickle.load(file)
        return (model_data['input_hidden_weights'], 
                model_data['hidden_output_weights'], 
                model_data['hidden_bias'], 
                model_data['output_bias'])
    else:
        print(f"Модель не найдена по пути: {file_path}")
        return None


# Функция нормализации входных данных X.
def normalize_data_X(data):
    X = np.array(data[:-1], dtype=float)
    min_vals = np.min(X, axis=1)
    max_vals = np.max(X, axis=1)

    return np.array([(X[i] - min_vals[i]) / (max_vals[i] - min_vals[i]) for i in range(len(X))])
# Функция нормализации выходных данных Y.
def normalize_data_Y(data):
    Y = np.array(data[-1], dtype=float)
    min_vals = np.min(Y)
    max_vals = np.max(Y)

    return np.array([(Y[i] - min_vals) / (max_vals - min_vals) for i in range(len(Y))])
# Функция денормализации данных.
def denormalize_data_Y(normalized_Y, min_val, max_val):
    return normalized_Y * (max_val - min_val) + min_val



# Функция инициализации синаптических весов и порогового значения каждого нейрона каждого слоя.
def initialize_weights(input_size, hidden_size, output_size):
    input_hidden_weights = np.random.uniform(-0.05, 0.05, (input_size, hidden_size))    # Между входным и скрытым слоем.
    hidden_output_weights = np.random.uniform(-0.05, 0.05, (hidden_size, output_size))  # Между скрытым и выходным слоем.
    hidden_bias = np.random.uniform(-0.05, 0.05, (hidden_size))                         # Смещения скрытого слоя.
    output_bias = np.random.uniform(-0.05, 0.05, (output_size))                         # Смещения выходного слоя.
    return input_hidden_weights, hidden_output_weights, hidden_bias, output_bias
# Функция активации - сигмоида (прямое распространение сигнала).
def sigmoid(x):
    return 1 / (1 + np.exp(-x))
# Производная сигмоиды (обратное распространение ошибки).
def sigmoid_derivative(sigm_x):
    return sigm_x * (1 - sigm_x)



# Прямое распространение сигнала.
def forward_propagation(input_data, input_hidden_weights, hidden_output_weights, hidden_bias, output_bias):
    # Выход скрытого слоя.
    hidden_layer_input = np.dot(input_data, input_hidden_weights) + hidden_bias # Матрица синаптических весов: 1-1, 2-1, 3-1, 4-1, 5-1 - это первые элементы каждой строки, и т.д.
                                                                                # Получили матрицу значений функции агрегата (сумматор).
    hidden_layer_output = sigmoid(hidden_layer_input)                           # Берем f(значение функции агрегата).
    
    # Выход выходного слоя.
    output_layer_input = np.dot(hidden_layer_output, hidden_output_weights) + output_bias # Аналогично выше.
    predicted_output = sigmoid(output_layer_input)                                        # Аналогично выше.

    # Таким образом, в predicted_output лежит то значение, которое нейросеть на данный момент определила корректным.
    # Для того, чтобы применить алгоритм обратного распространения ошибки, возвращаем значения, полученные на скрытом и выходном слоях.
    return hidden_layer_output, predicted_output
# Обратное распространение ошибки.
def backward_propagation(input_data, hidden_layer_output, predicted_output, target, input_hidden_weights, hidden_output_weights, hidden_bias, output_bias, learning_rate):
    # ШАГ 3. Для всех нейронов k последнего слоя подсчитать значения невязок.
    # Ошибка на выходном слое.
    output_error = target - predicted_output                           # error_k = dk - yk.
    output_delta = output_error * sigmoid_derivative(predicted_output) # Невязка: delta_k = yk(1-yk)(dk-yk), где dk - точное значение, yk - полученное НС по функции активации (сигмоида)
                                                                       # Производная сигмоиды равна, очевидно, sigm' = sigm * (1 - sigm), где sigm = 1/(1+e^(-x)).

    # ШАГ 4. Для каждого уровня n, начиная с предпоследнего - для каждого узла i уровня n вычислить невязку.
    # Ошибка на скрытом слое (учитывается, что по теор. Колмогорова скрытый слой - один).
    hidden_error = np.dot(output_delta, hidden_output_weights.T)            # error_j = delta_k * wjk.
    hidden_delta = hidden_error * sigmoid_derivative(hidden_layer_output)   # Невязка: delta_j = (delta_k * wjk) * yj(1-yj)
    
    # ШАГ 5. Для каждого ребра сети {i, j} обновить значения весов.
    # От скрытого слоя к выходному.
    hidden_output_weights += learning_rate * np.outer(hidden_layer_output, output_delta) # Синаптический вес: wjk = wjk + learning_rate * delta_k * yk.
    output_bias += learning_rate * output_delta                                          # Сдвиг: bk = bk + learning_rate * delta_k.

    # От входного слоя к скрытому.
    input_hidden_weights += learning_rate * np.outer(input_data, hidden_delta)           # Синаптический вес: wij = wij + learning_rate * delta_k * yk.
    hidden_bias += learning_rate * hidden_delta                                          # Сдвиг: bj = bj + learning_rate * delta_j.

    return input_hidden_weights, hidden_output_weights, hidden_bias, output_bias
# Функция обучения нейросети по алгоритму обратного распространения ошибки на входных данных.
def train_neural_network(data, targets, input_hidden_weights, hidden_output_weights, hidden_bias, output_bias, learning_rate, epochs, delta_threshold, output_file):
    # Для вычисления в среднем значений MSE и MAE, учитывая каждую эпоху обучения.
    MSE_mass = []
    MAE_mass = []
    for epoch in range(epochs):
        # Перемешивание данных
        data = np.array(data)
        indices = np.arange(len(targets)) # Создаем массив индексов.
        np.random.shuffle(indices) # Перемешиваем индексы.
        data = data[indices] # Соответственно перемешиваем примеры исходных данных.
        targets = targets[indices] # Точно так же перемешиваем примеры точных значений.

        #Массивы для хранений значений и рассчета (объективно) MSE и MAE.
        total_predictions = []  # Для хранения предсказаний на текущей эпохе.
        total_targets = []      # Для хранения реальных значений на текущей эпохе.
        
        for input_data, target in zip(data, targets):
            # ШАГ 2. Подать на вход сети очередной обучающий пример и подсчитать выходы.
            hidden_layer_output, predicted_output = forward_propagation(input_data, input_hidden_weights, hidden_output_weights, hidden_bias, output_bias)
            total_predictions.append(predicted_output)  # Сохраняем текущее предсказание.
            total_targets.append(target)                # Сохраняем реальное значение.
            
            # ШАГ 3-5. Исправление весов и сдвигов на основе алгоритма обратного распространения ошибки.
            input_hidden_weights, hidden_output_weights, hidden_bias, output_bias = backward_propagation(
                input_data, hidden_layer_output, predicted_output, target, 
                input_hidden_weights, hidden_output_weights, hidden_bias, output_bias, learning_rate
            )
        
        # После каждой эпохи вычисляем метрики.
        total_predictions = np.array(total_predictions)
        total_targets = np.array(total_targets)
        
        # MSE (Mean Squared Error)
        MSE = np.mean((total_targets - total_predictions) ** 2)
        # MAE (Mean Absolute Error)
        MAE = np.mean(np.abs(total_targets - total_predictions))
        # Добавление значений MSE и MAE в массивы.
        MSE_mass.append(MSE)
        MAE_mass.append(MAE)
        
        # Вывод метрик каждые 1000 эпох.
        if (epoch + 1) % 1000 == 0:
            write_to_file(output_file, f'Эпоха {epoch + 1},\tMSE: {MSE:.8f},\tMAE: {MAE:.8f}')
            print(f"НС прошла обучение на {epoch + 1}/{epochs} эпох.")
        
        # Проверка критерия остановки.
        if MSE < delta_threshold:  # Если ошибка меньше заданного порога.
            write_to_file(output_file, f'Обучение остановлено на эпохе {epoch + 1}, MSE: {MSE:.8f}, MAE: {MAE:.8f}.')
            break
    
    # Средняя ошибка на всех данных.
    mean_MSE = np.mean(MSE_mass)
    mean_MAE = np.mean(MAE_mass)
    write_to_file(output_file, f'Средяя MSE между реальными и предсказанными значениями: {mean_MSE:.8f}.')
    write_to_file(output_file, f'Средняя MAE между реальными и предсказанными значениями: {mean_MAE:.8f}.')
    
    return input_hidden_weights, hidden_output_weights, hidden_bias, output_bias

 

# Функция для тестирования нейросети.
def test_neural_network_to_file(test_size, output_file, data, targets, input_hidden_weights, hidden_output_weights, hidden_bias, output_bias, min_val_Y, max_val_Y):
    # Размер тестовой выборки.
    write_to_file(output_file, f"Размер тестовой выборки: {test_size}")
    
    # Перемешивание данных.
    data = np.array(data)
    indices = np.arange(len(targets))
    np.random.shuffle(indices)
    shuffled_data = data[indices]
    shuffled_targets = targets[indices]
    
    # Выбор test_size случайных примеров
    test_examples = shuffled_data[:test_size]   # Первые test_size примера после перемешивания.
    test_targets = shuffled_targets[:test_size] # Их соответствующие реальные значения.
    
    # Прогон через нейросеть.
    for i, (input_data, real_value) in enumerate(zip(test_examples, test_targets)):
        _, predicted_output = forward_propagation(input_data, input_hidden_weights, hidden_output_weights, hidden_bias, output_bias)
        
        # Денормализация.
        # Реальное и предсказанное значения
        denorm_real = denormalize_data_Y(np.array([real_value]), min_val_Y, max_val_Y)[0]
        denorm_predicted = denormalize_data_Y(predicted_output, min_val_Y, max_val_Y)[0]
        
        # Запись результатов в файл
        write_to_file(output_file, f"Пример {i + 1}:")
        write_to_file(output_file, f"  Реальное значение (денорм.): {denorm_real:.8f}")
        write_to_file(output_file, f"  Предсказанное значение (денорм.): {denorm_predicted:.8f}")
        write_to_file(output_file, f"  Абсолютная ошибка: {np.abs(denorm_real - denorm_predicted):.8f}")
        print(f"Тестовый пример {i + 1} успешно был решен НС.")
# Основная функция.
def main():
    file_path = "Домохозяйства_в_районах_РТ.txt"
    output_file = "output_log.txt"
    trained_model_path = "trained_neural_network.pkl"
    
    # Очищаем файл перед записью.
    with open(output_file, 'w') as f:
        f.write('Training Log...\n\n')

    # ШАГ 0. Чтение исходных данных и их нормализация.
    data = np.array(load_data(file_path), dtype=float)

    # Нормализация входных и выходных данных.
    normalized_X = normalize_data_X(data.T)
    normalized_Y = normalize_data_Y(data.T)

    # ЗАПРОС ПОЛЬЗОВАТЕЛЯ, ЧТО ДЕЛАТЬ ДАЛЬШЕ.
    user_choice = input("Хотите использовать уже обученную модель (y/n [any symbols])? ").strip().lower()
    if user_choice == 'y':
        print("Загружаем обученную модель...")
        input_hidden_weights, hidden_output_weights, hidden_bias, output_bias = load_trained_model(trained_model_path)
    else:
        # Запись в файл.
        write_to_file(output_file, 'Исходные данные успешно загружены.')
        write_to_file(output_file, f'Размер обучающей выборки: {len(data.T[0])} примеров.')
        print("Обучение нейросети...")
        # ШАГ 1. Инициализация синмаптических весов и сдвига.
        input_size = 5   # (т.к. 5 признаков)
        hidden_size = 11 # (по теор. Колмогорова)
        output_size = 1  # (т.к. 1 целевой параметр)   
    
        input_hidden_weights, hidden_output_weights, hidden_bias, output_bias = initialize_weights(input_size, hidden_size, output_size)

        # ШАГ 6. Повторить шаги 2-5 для следующего обучающего примера.
        learning_rate = 0.1
        epochs = 10000
        delta_threshold = 0.003 # Условие из индивидуального задания.
    
        input_hidden_weights, hidden_output_weights, hidden_bias, output_bias = train_neural_network(
            normalized_X.T, normalized_Y.T, 
            input_hidden_weights, hidden_output_weights, 
            hidden_bias, output_bias, 
            learning_rate, epochs,
            delta_threshold, output_file
        )

        # ШАГ 7. Выдать и сохранить параметры обученной нейросети.
        save_neural_network(trained_model_path, 
                        input_hidden_weights, hidden_output_weights, 
                        hidden_bias, output_bias, output_file)
        
    print(f"Лог многослойного персептрона обратного распространения ошибки сохранен в файл: {output_file}.")

    # ШАГ 8. Тестирование нейросети.
    test_size = 10
    test_neural_network_to_file(
        test_size,                # Размер тестовой выборки
        output_file, 
        normalized_X.T,           # Исходные данные
        normalized_Y.T,           # Исходные цели каждого набора данных
        input_hidden_weights,     # Обученные веса входной слой -> скрытый слой
        hidden_output_weights,    # Обученные веса скрытый слой -> выходной слой
        hidden_bias,              # Смещения скрытого слоя
        output_bias,              # Смещения выходного слоя
        np.min(np.array(data.T[-1], dtype=float)),
        np.max(np.array(data.T[-1], dtype=float))
    )
    # Запуск программы.
if __name__ == '__main__':
    main()