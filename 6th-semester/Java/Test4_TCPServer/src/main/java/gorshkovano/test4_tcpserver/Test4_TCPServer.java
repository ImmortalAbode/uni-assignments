package gorshkovano.test4_tcpserver;

/*********
*Пример 3*
**********/
import java.io.*;
import java.net.*;
//Импорт классов для настройки корректного отображения кириллических символов из пакета java.io в NetBeans.
import java.io.PrintStream;
import java.io.UnsupportedEncodingException;

public class Test4_TCPServer
{
    public static final int PORT = 2500;
    private static final int TIME_SEND_SLEEP = 100;
    private static final int COUNT_TO_SEND = 10;
    private ServerSocket servSocket;
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
        Test4_TCPServer tcpServer = new Test4_TCPServer();
        tcpServer.go();
    }
    public Test4_TCPServer()
    {
        try
        {
            servSocket = new ServerSocket(PORT);
        }
        catch(IOException e)
        {
            System.err.println("Не удаётся открыть сокет для сервера: " + e.toString());
        }
    }
    public void go()
    {
        class Listener implements Runnable
        {
            Socket socket;
            public Listener(Socket aSocket)
            {
                socket = aSocket;
            }
            public void run()
            {
                try
                {
                    System.out.println("Слушатель запущен");
                    int count = 0;
                    OutputStream out = socket.getOutputStream();
                    OutputStreamWriter writer = new OutputStreamWriter(out);
                    PrintWriter pWriter = new PrintWriter(writer);
                    while(count < COUNT_TO_SEND)
                    {
                        count++;
                        pWriter.print(((count>1) ? "," : "") + "говорит " + count);
                        Thread.sleep(TIME_SEND_SLEEP);
                    }
                    pWriter.close();
                }
                catch(IOException e)
                {
                    System.err.println("Исключение: " + e.toString());
                } 
                catch (InterruptedException e) 
                {
                    System.err.println("Исключение: " + e.toString());
                }
            }
        }
        System.out.println("Сервер запущен...");
        while(true)
        {
            try
            {
                Socket socket = servSocket.accept();
                Listener listener = new Listener(socket);
                Thread thread = new Thread(listener);
                thread.start();
            }
            catch(IOException e)
            {
                System.err.println("Исключение: " + e.toString());
            }
        }
    }
}
