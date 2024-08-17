package gorshkovano.test4;

//Импорт классов для настройки корректного отображения кириллических символов из пакета java.io в NetBeans.
import java.io.PrintStream;
import java.io.UnsupportedEncodingException;
//Для примера 2.
import java.io.*;
import java.net.*;

/*********
*Пример 1*
**********/
/* Потоки*/
// Класс потокового объекта.
class A extends Thread 
{
    public void run() 
    {
        for(int i=0; i < 5; i++) 
        {
            System.out.print ("A");
            try 
            {
                Thread.sleep (100);
            }
            catch (InterruptedException e){}
        }
    }
}
// Класс с потоковой функцией.
class B implements Runnable 
{
    public void run() 
    {
        for (int i=0; i < 5; i++) 
        {
            System.out.print ("B");
            try
            {
                Thread.sleep (100);
            }
            catch (InterruptedException e){}
        }
    }
}

public class Test4 
{
    public static void main (String[] args) 
    {
        //Установка кодировки для вывода.
        try 
        {
            System.setOut(new PrintStream(System.out, true, "UTF-8"));
        } 
        catch (UnsupportedEncodingException e)
        {
            e.printStackTrace();
        }
        //Пример 1.
        A a = new A();//Первый способ создания потока
        B b = new B();//Второй способ создания потока (Шаг.1)
        Thread t = new Thread (b,"thread");//Второй способ создания потока(Шаг.2)
        a.start();//Запуск потоков А
        t.start();//Запуск потоков B
        //Пример 2.
        try 
        {
            URL url = new URL("http://www.ru");
            LineNumberReader r = new LineNumberReader(
            new InputStreamReader(url.openStream()));
            String s = r.readLine();
            while (s!=null) {
            System.out.println(s);
            s = r.readLine();
            }
            System.out.println(r.getLineNumber());
            r.close();
        }
        catch (MalformedURLException e)
        {
            e.printStackTrace();
        }
        catch (IOException e) 
        {
            e.printStackTrace();
        }
    }
}