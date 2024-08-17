package gorshkovano.test4_udpclient;

/*********
*Пример 4*
**********/
import java.io.*;
import java.net.*;
//Импорт классов для настройки корректного отображения кириллических символов из пакета java.io в NetBeans.
import java.io.PrintStream;
import java.io.UnsupportedEncodingException;

public class Test4_UDPClient 
{
    public static final int LENGTH_PACKET = 60;
    public static final String HOST = "localhost";
    public static final int PORT = 2345;
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
        try
        {
            //-----------------------------------------------------------------
            //отправка сообщения на сервер
            //-----------------------------------------------------------------
            byte data[] = ("hello!!! % 1234 5-9*6;").getBytes();
            InetAddress addr = InetAddress.getByName(HOST);
            DatagramSocket socket = new DatagramSocket();
            DatagramPacket packet = new DatagramPacket(data, data.length, addr, PORT);
            socket.send(packet);
            System.out.println("Сообщение отправлено...");
            //-----------------------------------------------------------------
            //приём сообщения с сервера
            //-----------------------------------------------------------------
            byte data2[];
            data2 = new byte[LENGTH_PACKET];
            packet = new DatagramPacket(data2, data2.length);
            socket.receive(packet);
            System.out.println((new String(packet.getData())).trim());
            //-----------------------------------------------------------------
            //закрытие сокета
            //-----------------------------------------------------------------
            socket.close();
        }
        catch(SocketException e)
        {
            e.printStackTrace();
        }
        catch(IOException e)
        {
            e.printStackTrace();
        }
    }
}
