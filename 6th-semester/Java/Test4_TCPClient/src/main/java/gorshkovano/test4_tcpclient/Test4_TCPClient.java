package gorshkovano.test4_tcpclient;

/*********
*Пример 3*
**********/
import java.io.*;
import java.net.*;
//Импорт классов для настройки корректного отображения кириллических символов из пакета java.io в NetBeans.
import java.io.PrintStream;
import java.io.UnsupportedEncodingException;

public class Test4_TCPClient implements Runnable 
{
    public static final int PORT = 2500;
    public static final String HOST = "localhost";
    public static final int CLIENT_COUNT = 6;
    public static final int READ_BUFFER_SIZE = 10;
    private String name = null;
    public Test4_TCPClient(String s)
    {
        name = s;
    }
    public void run()
    {
        char[] readed = new char[READ_BUFFER_SIZE];
        StringBuffer strBuff = new StringBuffer();
        try
        {
            Socket socket = new Socket(HOST, PORT);
            InputStream in = socket.getInputStream();
            InputStreamReader reader = new InputStreamReader(in);
            while(true)
            {
                int count = reader.read(readed, 0, READ_BUFFER_SIZE);
                if(count == -1)
                    break;
                strBuff.append(readed, 0, count);
                Thread.yield();
            }
        } 
        catch (UnknownHostException e) 
        {
            System.err.println("Исключение: " + e.toString());
        } 
        catch (IOException e) 
        {
            System.err.println("Исключение: " + e.toString());
        }
        System.out.println("Клиент " + name + " прочёл: " + strBuff.toString());
    }
    public static void main(String[] args) 
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
        String name = "имя";
        for(int i = 1; i <= CLIENT_COUNT; i++)
        {
            Test4_TCPClient ja = new Test4_TCPClient(name+i);
            Thread th = new Thread(ja);
            th.start();
        }
    } 
}
