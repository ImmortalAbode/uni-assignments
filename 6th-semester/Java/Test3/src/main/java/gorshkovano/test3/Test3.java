package gorshkovano.test3;

/*Уведомление*/
import java.io.*;
import java.util.*;

/*******
*Тест 1*
********/
/*Явное событие*/
//Интерфейс события.
interface IEv 
{
    void Handler();
}
//Класс источника события.
class Source 
{
    IEv iEv;
    //Конструктор.
    Source (IEv iEv) 
    {
        this.iEv = iEv;
    }
    //Генерировать событие.
    void genEv() 
    {
        iEv.Handler();
    } 
}
//Класс приёмника события.
class Receiver implements IEv 
{
    //Обработчик.
    public void Handler() 
    {
        System.out.println ("OK");
    }
}
/*******
*Тест 2*
********/
class beWatched extends Observable 
{//Класс наблюдаемого объекта
    void notifyObs() 
    {
        setChanged();
        notifyObservers(new Integer(55));
    }
}
class Watcher implements Observer 
{//Класс обозревателя
    public void update(Observable obs, Object arg) 
    {
        System.out.println ("received " + ((Integer)arg).intValue());
    }
}

class Test3 
{
    public static void main (String[] args) 
    {
        //Тест 1.
        Receiver receiver = new Receiver();//Создать объект приемника.
        Source source = new Source(receiver);//Создать объект источника.
        source.genEv();
        //Тест 2.
        Watcher w = new Watcher();//Создать объект приемника
        beWatched bW = new beWatched();//Создать объект источника
        bW.addObserver(w);
        bW.notifyObs();//Уведомить
        
        /*********
        *Пример 1*
        **********/
        /*Пример ввод с консоли*/
        Scanner sc = new Scanner(System.in);
        int i = 0;
        System.out.print("Input an integer: ");
        //Возвращает истинну если с потока ввода можно считать целое число.
        if(sc.hasNextInt()) 
        {
            /*Аналогично метод hasNextDouble(), применённый объекту класса Scanner, проверяет,
            можно ли считать с потока ввода вещественное число типа double, а метод nextDouble() —
            считывает его.*/
            //Считывает целое число с потока ввода и сохраняем в переменную.
            i = sc.nextInt();
            System.out.println(i*2);
        } 
        else 
        {
            System.out.println("См. выше ^^^");
        }
        /*Метод nextLine(), позволяющий считывать целую последовательность символов, т.е.
        строку. Далее создаётся два таких объекта, потом в них поочерёдно записывается ввод
        пользователя, на экран выводится одна строка, полученная объединением введённых
        последовательностей символов.
        */
        Scanner sc2 = new Scanner(System.in);
        String s1, s2;
        s1 = sc2.nextLine();
        s2 = sc2.nextLine();
        System.out.println(s1 + s2);
        
        
        /*********
        *Пример 2*
        **********/
        /*Пример работы с текстовым файлом*/
        //Создание файла и запись в него ----------------------------------------
        String filename = "log.txt";
        File f = new File(filename);
        try
        {
            if(!f.exists()) 
                f.createNewFile();
            PrintWriter pw = new PrintWriter(f.getAbsoluteFile());
            try
            {
                pw.println("2 ~!");
                pw.println("4 ~!");
                pw.println("6 ~!");
                pw.println("8 ~!");
            }
            finally
            {
                pw.close();
            }
        }
        catch(IOException e)
        {
            throw new RuntimeException();
        }
        //Чтение из файла -------------------------------------------------------
        StringBuilder sb = new StringBuilder();
        if(f.exists())
        {
            try
            {
                BufferedReader br = new BufferedReader(new FileReader(f.getAbsoluteFile()));
                try
                {
                    String s;
                    //Построчное чтение.
                    while((s = br.readLine())!=null)
                    {
                        sb.append(s);
                        sb.append("\n");
                    }
                }
                finally
                {
                    br.close();
                }
            }
            catch(IOException e)
            {
                throw new RuntimeException();
            }
        }
        //В sb.toString() хранится текст файла.
        System.out.print(sb.toString());
        /*Для обновления файла можно сперва прочитать файл в переменную типа String,
        как это сделано в секции чтение из файла,
        а затем, сложив его с новым содержимым, записать в файл*/
        //Удаление файла --------------------------------------------------------
        //f.delete();
    }
}
