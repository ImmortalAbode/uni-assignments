package gorshkovano.laba4_client;

import java.io.*;
import java.net.*;
import java.util.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class Laba4_Client implements Runnable
{
    //Константы.
    public static final int CLIENT_COUNT = 1;
    public static final int READ_BUFFER_SIZE = 10;
    //Работа с файлом.
    public int port;
    public String host;
    private final File f_client_log;
    //Имя клиента.
    private String name = null;
    //Отдельный поток ввода для каждого клиента.
    Scanner scanner;
    
    public Laba4_Client(String s, String host, int port, File f_client_log)
    {
        this.name = s;
        this.host = host;
        this.port = port;
        this.f_client_log = f_client_log;
        this.scanner = new Scanner(System.in);
        System.out.println("Client log file path: " + this.f_client_log.getAbsolutePath());
        LocalDateTime currentDateTime = LocalDateTime.now();
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");
        String formattedDateTime = currentDateTime.format(formatter);
        System.out.println("The Client was started succesfully. Date and Time: " + formattedDateTime);
        log("The Client was started succesfully. Date and Time: " + formattedDateTime);
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
            System.err.println("Exception: " + e.toString());
        }
        if (args.length != 3) 
        {
            System.out.println("Error: The command line arguments must specify the host, port, and file for the client log. Correct and try again.");
            return;
        }

        String host = args[0];
        int port = -1;
        if (isValidPort(args[1]))
        {
            port = Integer.parseInt(args[1]);
        }
        File f_client_log = checkAndGetLogClientFile(args[2]);

        String name = "Client";
        for (int i = 1; i <= CLIENT_COUNT; i++) 
        {
            Laba4_Client ja = new Laba4_Client(name + i, host, port, f_client_log);
            Thread th = new Thread(ja);
            th.start();
        }
    }
    @Override
    public void run()
    {
        char[] readed = new char[READ_BUFFER_SIZE];
        StringBuffer strBuff = new StringBuffer();
        try
        {
            //Создание сокета для подключения к серверу.
            Socket socket = new Socket(host, port);
            //Для чтения сообщений от сервера.
            InputStream in = socket.getInputStream();
            InputStreamReader reader = new InputStreamReader(in);
            //Для отправки сообщений серверу.
            OutputStream out = socket.getOutputStream();
            OutputStreamWriter writer = new OutputStreamWriter(out);
            PrintWriter pWriter = new PrintWriter(writer, true);
            
            /* Чтение ввода от текущего пользователя (клиента) */
            System.out.println("Enter the operand and operation (+ or -), or '=' to complete:");
            while(true)
            {
                //Ввод части выражения и отправка его серверу.
                System.out.print("Part: ");
                String part_expression = scanner.nextLine();
                if (part_expression.length() == 0 || !isValidPartOfExpression(part_expression)) 
                {
                    System.out.println("Incorrect part of expression! Please enter a part of expression correctly:");
                }
                else
                {
                    pWriter.println(part_expression);
                    //Проверка окончания ввода частей выражения.
                    char operator = part_expression.charAt(part_expression.length() - 1);
                    if (operator == '=')
                        break;
                }
            }
            
            //Чтение сообщений от сервера.
            while(true)
            {
                int count = reader.read(readed, 0, READ_BUFFER_SIZE);
                if(count == -1) break;
                strBuff.append(readed, 0, count);
                Thread.yield();
            }
        }
        catch (UnknownHostException e)
        {
            System.err.println("Exception: " + e.toString());
        } 
        catch (IOException e)
        {
            System.err.println("Exception: " + e.toString());
        }
        System.out.println("Client " + this.name + " have read: " + strBuff.toString());
        log("Received expression from server:\n" + strBuff.toString());
    }
    //---ВСПОМОГАТЕЛЬНЫЕ МЕТОДЫ---//
    private static boolean isValidPartOfExpression(String part_expression)
    {
        char operator = part_expression.charAt(part_expression.length() - 1);
        String operand = part_expression.substring(0, part_expression.length() - 1);
        if (part_expression.isEmpty() || operator != '-' && operator != '+' && operator != '=')
        {
            return false;
        }
        try 
        {
            Double.valueOf(operand);
        }
        catch (NumberFormatException e)
        {
            return false;
        }
        return true;
    }
    private void log(String message) 
    {
        try
        {
            PrintWriter pw = new PrintWriter(new FileWriter(this.f_client_log.getAbsoluteFile(), true));
            pw.println(message);
            pw.close();
        } 
        catch (IOException e) 
        {
            System.err.println("Exception: " + e.toString());
        }
    }   
    private static File checkAndGetLogClientFile(String clientFileLogPath)
    {
        System.out.println("The path of the log file for client is: " + clientFileLogPath);
        File tempClientFileLogPath = new File(clientFileLogPath);
        if (tempClientFileLogPath.exists())
        {
            System.out.println("Client log file was successfully detected. Path: " + tempClientFileLogPath.getAbsolutePath());
        }
        else
        {
            try
            {
                tempClientFileLogPath.createNewFile();
                System.out.println("Client log file created succesfully. Path: " + tempClientFileLogPath.getAbsolutePath());
            }
            catch (IOException e)
            {
                System.out.println("Exception: " + e.getMessage());
                return null;
            }
        }
        return tempClientFileLogPath;
    }
    private static boolean isValidPort(String str_port)
    {
        try
        {
            int port = Integer.parseInt(str_port);
            return port >= 0 && port <= 65535;
        }
        catch (NumberFormatException e)
        {
            System.out.println("Error: The port number must be a positive integer between 0 and 65535.");
            return false;
        }
    }
}
