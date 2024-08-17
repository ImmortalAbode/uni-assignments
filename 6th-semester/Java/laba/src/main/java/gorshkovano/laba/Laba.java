/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 */

//Автоматически созданный пакет при создании проекта для его структурирования.
package gorshkovano.laba;

/**
 *
 * @author Andrew
 */

//Импорт классов для настройки корректного отображения кириллических символов из пакета java.io в NetBeans.
import java.io.PrintStream;
import java.io.UnsupportedEncodingException;

//Импорт класса ArrayList для работы со списком из пакета java.util.
import java.util.ArrayList;
import java.util.List;

//Автоматически созданный класс при создании проекта.
public class Laba {
    public static void main(String[] args) {
        //Установка кодировки для вывода.
        try 
        {
            System.setOut(new PrintStream(System.out, true, "UTF-8"));
        } 
        catch (UnsupportedEncodingException e)
        {
            e.printStackTrace();
        }

        // Если нет аргументов командной строки, выводится сообщение об ошибке и программа завершается.
        if (args.length == 0) {
            System.out.println("Ошибка! Пожалуйста, введите аргументы командной строки в виде последовательности целых чисел через пробел.");
            return;
        }
        
        // Использование коллекции List и массивов ArrayList.
        List<Integer> evenNegativeNumbers = new ArrayList<>();//Для четных отрицательных целых чисел.
        List<Integer> oddPositiveNumbers = new ArrayList<>();//Для нечетных положительных целых чисел.

        // Обработка каждого аргумента командной строки.
        for (String arg : args) {
            // Преобразование строки в целое число.
            try 
            {
                int num = Integer.parseInt(arg);
                // Проверка четности и отрицательности числа.
                if (num < 0 && num % 2 == 0) 
                {
                    evenNegativeNumbers.add(num);
                }
                if (num > 0 && num % 2 != 0)
                {
                    oddPositiveNumbers.add(num);
                }
            }
            catch (NumberFormatException e) 
            {
                // Вывод сообщения об ошибке и завершение программы, если введено некорректное число.
                System.out.println("Ошибка! Введено некорректное число: " + arg);
                return;
            }
        }

        // Вывод результатов.
        int sumEvenNegativeNumbers = 0; //Сумма четных отрицательных чисел.
        int sumOddPositiveNumbers = 0; //Сумма нечетных положительных чисел.
        for (int num : evenNegativeNumbers)
        {
            sumEvenNegativeNumbers += num;
        }
        for (int num : oddPositiveNumbers)
        {
            sumOddPositiveNumbers += num;
        }
        System.out.println("Сумма четных отрицательных чисел: " + sumEvenNegativeNumbers);
        System.out.println("Сумма нечетных положительных чисел: " + sumOddPositiveNumbers);
    }
}
