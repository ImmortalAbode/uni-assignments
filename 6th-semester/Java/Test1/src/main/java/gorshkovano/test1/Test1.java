/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 */

package gorshkovano.test1;

/**
 *
 * @author Andrew
 */
import java.util.ArrayList;//для работы со списком.
//import java.util.*;//Можно включить ппакет целиком
public class Test1 
{
    public static void main(String[] args)
    {
        ArrayList<String> al1 = new ArrayList<>();//создане списка для нечётных чисел
        ArrayList<String> al2 = new ArrayList<>();//создане списка для чётных чисел
        for (String x : args) //Вывод всех заданных параметров командной строки
        {
            /* преобразвание строки, хранящейся в переменной "х" в целое число
            и проверка этого числа на чётность*/
            if (Integer.parseInt(x) % 2 == 0) 
            {
                al2.add(x);//добавление в список чётного
            } 
            else 
            {
                al1.add(x);//добавление в список нечётного
            }
        }
        System.out.println(al1);//вывод "нечётного" списка
        System.out.println(al2);//вывод "чётного" списка
        //то же цикл, но как в СИ
        //for (int i = 0; i < args.length; i++) {
        // System.out.println(args[i]);//
    }
}
