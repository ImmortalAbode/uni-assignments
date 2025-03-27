# -*- coding: Windows-1251 -*-

# Функции принадлежности
def triangular(x, a, b, c):
    if a <= x <= b:
        return (x - a) / (b - a)
    elif b <= x <= c:
        return (c - x) / (c - b)
    else:
        return 0
def trapezoidal(x, a, b, c, d):
    if a <= x <= b:
        return (x - a) / (b - a)
    elif b <= x <= c:
        return 1
    elif c <= x <= d:
        return (d - x) / (d - c)
    else:
        return 0

# Функции фаззификации
def fuzzify_delta_T(value):
    return {
        "малая": triangular(value, -15, 0, 15),
        "средняя": triangular(value, 0, 15, 30),
        "большая": trapezoidal(value, 15, 30, 35, 100),
    }
def fuzzify_dT_dt(value):
    return {
        "малая": triangular(value, -0.15, 0, 0.15),
        "средняя": triangular(value, 0, 0.15, 0.3),
        "большая": trapezoidal(value, 0.15, 0.3, 0.4, 100),
    }
def fuzzify_compressor_speed(value):
    return {
        "очень малая": trapezoidal(value, -31.5, 0, 3, 32),
        "малая": triangular(value, 17, 33, 47),
        "средняя": triangular(value, 49, 63, 79),
        "большая": triangular(value, 81, 93, 111),
        "очень большая": trapezoidal(value, 105, 123, 133, 1000),
    }

# Правила нечеткой логики
rules = [
    (["малая", "малая"], "очень малая"),
    (["малая", "средняя"], "малая"),
    (["малая", "большая"], "средняя"),
    (["средняя", "малая"], "малая"),
    (["средняя", "средняя"], "средняя"),
    (["средняя", "большая"], "большая"),
    (["большая", "малая"], "средняя"),
    (["большая", "средняя"], "большая"),
    (["большая", "большая"], "очень большая"),
]

# Агрегация правил
def aggregate_rules(delta_T, dT_dt):
    aggregated = {"очень малая": 0, "малая": 0, "средняя": 0, "большая": 0, "очень большая": 0}
    for antecedents, consequent in rules:
        rule_value = min(delta_T[antecedents[0]], dT_dt[antecedents[1]])
        aggregated[consequent] = max(aggregated[consequent], rule_value)
    return aggregated

# Дефаззификация: метод центра тяжести
def defuzzify(aggregated):
    numerator = 0
    denominator = 0
    x_range = list(range(136))
    for x in x_range:
        membership = max(
            trapezoidal(x, -31.5, 0, 3, 32) * aggregated["очень малая"],
            triangular(x, 17, 33, 47) * aggregated["малая"],
            triangular(x, 49, 63, 79) * aggregated["средняя"],
            triangular(x, 81, 93, 111) * aggregated["большая"],
            trapezoidal(x, 105, 123, 133, 1000) * aggregated["очень большая"],
        )
        numerator += x * membership
        denominator += membership
    return numerator / denominator if denominator != 0 else 0

# Функция запроса ввода неотрицательных чисел у пользователя
def get_non_negative_float(prompt):
    while True:
        user_input = input(prompt)
        if user_input.lower() == 'exit':
            return None
        try:
            value = float(user_input)
            if value >= 0:
                return value
            else:
                print("Ошибка: введите неотрицательное число.")
        except ValueError:
            print("Ошибка: введите корректное число.")

# Функция записи данных в файл
def log_to_file(file_name, data):
    with open(file_name, 'a') as file:
        file.write(data + "\n")

# Основная функция
def main():
    file_path = "input_output_log.txt"
    while True:
        # Запрос у пользователя значения для каждого параметра
        delta_T_value = get_non_negative_float("Введите значение для разности температур (delta_T) (неотрицательное число или 'exit' для выхода): ")
        if delta_T_value is None:
            print("Выход из программы.")
            break

        dT_dt_value = get_non_negative_float("Введите значение для скорости изменения температуры (dT/dt) (неотрицательное число или 'exit' для выхода): ")
        if dT_dt_value is None:
            print("Выход из программы.")
            break

        # Запись в файл
        log_to_file(file_path, f"delta_T: {delta_T_value}")
        log_to_file(file_path, f"dT/dt: {dT_dt_value}")

        # Фаззификация
        delta_T = fuzzify_delta_T(delta_T_value)
        dT_dt = fuzzify_dT_dt(dT_dt_value)
   
        # Вывод
        print(f"Результат фаззификации:\n{delta_T},\n{dT_dt}")
        log_to_file(file_path, f"Результат фаззификации:\n{delta_T},\n{dT_dt}")

        # Агрегация
        aggregated = aggregate_rules(delta_T, dT_dt)
        
        # Вывод
        print(f"Результат агрегации:\n{aggregated}")
        log_to_file(file_path, f"Результат агрегации:\n{aggregated}")

        # Дефаззификация
        compressor_speed = defuzzify(aggregated)
        print(f"Результат частоты вращения компрессора: {compressor_speed:.5f}\n")
        log_to_file(file_path, f"Результат частоты вращения компрессора: {compressor_speed:.5f}\n")

        # Запрос на продолжение или выход
        continue_input = input("Хотите ввести другие значения? (y [any symbols] / exit): ").lower()
        if continue_input == "exit":
            print("Выход из программы.")
            break

if __name__ == "__main__":
    main()
