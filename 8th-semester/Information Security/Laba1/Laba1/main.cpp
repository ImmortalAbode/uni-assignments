#include <iostream>
#include <cstdlib> //std::srand() и std::rand()
#include <ctime> //std::time() - вернуть время в секундах с 01.01.1970
#include <string>

//ГПСЧ для генерации случайных чисел в заданном диапазоне.
static int getRandomNumber(int min, int max) 
{
    return min + std::rand() % (max - min + 1);
}

//Функция для генерации случайного пароля.
static std::string generatePassword(int length) 
{
    const std::string alphabet = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ!\"#$%&\'()*";
    std::string password = "";
    for (int i{}; i < length; ++i) 
    {
        //Случайный индекс из alphabet.
        int randomIndex = getRandomNumber(0, alphabet.size() - 1); 
        password += alphabet[randomIndex];
    }
    return password;
}

int main() 
{
    //std::setlocale(LC_ALL, "RUS");
    std::system("chcp 1251 > nul");
    //std::system("color F0");
    //std::srand() используется в std::rand() для получения разных последовательностей случайных чисел.
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    //Количество паролей и их длина.
    const int count{ 20 };
    const int length{ 7 };

    //Генерация 20 паролей длиной 7 символов.
    for (int i{}; i < count; ++i)
        std::cout << generatePassword(length) << "\n";

    std::system("chcp 866 > nul");
    return 0;
}
