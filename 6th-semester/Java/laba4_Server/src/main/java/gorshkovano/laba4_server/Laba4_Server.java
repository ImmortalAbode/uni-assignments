package gorshkovano.laba4_server;

import java.io.*;
import java.net.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class Laba4_Server
{
    //Константы.
    public static final String FILE_SETTINGS_PATH = "D:\\KAI\\Технологии программирования на платформе Java\\laba4_Server\\FileSettings.txt";
    private static final int TIME_SEND_SLEEP = 100;
    //Работа с файлами.
    private static File f_server_log;
    //Сокет для сервера.
    private ServerSocket servSocket;
    //Уникальный номер клиента в текущей сессии сервера.
    private int clientNumber = 0;
    
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
        Laba4_Server tcpServer = new Laba4_Server(args);
        tcpServer.go();
    }
    public Laba4_Server(String[] args)
    {
        try
        {
            int server_port = getServerPortFromFile(FILE_SETTINGS_PATH);
            f_server_log = checkAndGetLogServerFile(args);
            if (f_server_log != null)
            {
                LocalDateTime currentDateTime = LocalDateTime.now();
                DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");
                String formattedDateTime = currentDateTime.format(formatter);
                System.out.println("The Server was started succesfully. Date and Time: " + formattedDateTime);
                log("The server was started succesfully. Date and Time: " + formattedDateTime);
                servSocket = new ServerSocket(server_port);
            }
            else
            {
                System.exit(1);
            }
        }
        catch(IOException e)
        {
            System.out.println("Error: Unable to open socket for the server:" + e.getMessage());
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
            @Override
            public void run(){
                ++clientNumber;
                System.out.println("Client Client" + clientNumber + " is connected.");
                log("Client Client" + clientNumber + " is conneceted.");                
                
                try
                {
                    //Для чтения сообщений от клиента.
                    InputStream in = socket.getInputStream();
                    InputStreamReader reader = new InputStreamReader(in);
                    BufferedReader bReader = new BufferedReader(reader);
                    //Для отправки сообщений клиенту.
                    OutputStream out = socket.getOutputStream();
                    OutputStreamWriter writer = new OutputStreamWriter(out);
                    PrintWriter pWriter = new PrintWriter(writer);
                    //Строка выражения.
                    String expression = "";
                    String part_expression;
                    while ((part_expression = bReader.readLine()) != null) 
                    {
                        System.out.println("Listener is running.");
                        // Добавляем полученные данные к строке выражения.
                        expression += part_expression;
                        // Если встречен знак '=', выходим из цикла.
                        if ('=' == part_expression.charAt(part_expression.length() - 1))
                        {                           
                            String result = getResultFromServer(expression);
                            pWriter.println("Result: " + result);
                            break;
                        }
                    }
                    pWriter.close();
                    Thread.sleep(TIME_SEND_SLEEP);
                    log("Received expression from client:\n" + expression);
                    System.out.println("Client Client" + clientNumber + " is disconnected.");
                    log("Client Client" + clientNumber + " is disconnected.\n");
                    --clientNumber;
                }
                catch(IOException e)
                {
                    System.out.println("Client " + clientNumber + " is disconnected.");
                    log("Client " + clientNumber + " is disconnected.\n");
                } 
                catch (InterruptedException e)
                {
                    System.err.println("Exception: " + e.toString());
                }
            } 
        }
        System.out.println("Server is running...");
        while(true)
        {
            try
            {        
                Socket socket = servSocket.accept();
                Listener clientHandler = new Listener(socket);
                Thread thread = new Thread(clientHandler);
                thread.start();
            }
            catch(IOException e)
            {
                System.out.println("Exception: " + e.toString());
            }
        }
    }
    //---ВСПОМОГАТЕЛЬНЫЕ МЕТОДЫ---//
    private static String getResultFromServer(String expression)
    {
        //Удаляем символ '=' из строки.
        expression = expression.substring(0, expression.length() - 1);
        String[] operands = expression.split("(?=[+-])");
        double result = 0;
        for (int i = 0; i < operands.length; i++)
        {
            try
            {
                double number = Double.parseDouble(operands[i]);
                if (i == 0)
                {
                    result += number;
                }
                else
                {
                    // Получаем оператор
                    char operator = operands[i].charAt(0); 
                    // Получаем операнд
                    double operand = Double.parseDouble(operands[i].substring(1));

                    // Применяем оператор к результату
                    switch (operator) 
                    {
                        case '+' -> result += operand;
                        case '-' -> result -= operand;
                        default -> {}
                    }
                }
            }
            catch(NumberFormatException e)
            {
                return ("Error: The specified value in the message, " + operands[i] + " is not a number.");
            }
            catch(ArithmeticException e)
            {
                return ("Error: Overflow occurred.");
            }
        }
        return String.valueOf(result);
    }
    private void log(String message) 
    {
        try
        {
            PrintWriter pw = new PrintWriter(new FileWriter(this.f_server_log.getAbsoluteFile(), true));
            pw.println(message);
            pw.close();
        } 
        catch (IOException e) 
        {
            System.err.println("Exception: " + e.toString());
        }
    }   
    private static File checkAndGetLogServerFile(String[] args)
    {
        if (args.length != 1)
        {
            System.out.println("Error: The command line arguments do not specify a file for the server log or there too many arguments. Correct and try again.");
            return null;
        }
        else
        {
            System.out.println("The path of the log file for server is: " + args[0]);
            File tempServerFileLogPath = new File(args[0]);
            if (tempServerFileLogPath.exists())
            {
                System.out.println("Server log file was successfully detected. Path: " + tempServerFileLogPath.getAbsolutePath());
            }
            else
            {
                try
                {
                    tempServerFileLogPath.createNewFile();
                    System.out.println("Server log file created succesfully. Path: " + tempServerFileLogPath.getAbsolutePath());
                }
                catch (IOException e)
                {
                    System.out.println("Exception: " + e.getMessage());
                    return null;
                }
            }
            return tempServerFileLogPath;
        }
    }
    private static boolean isValidPort(String str_server_port)
    {
        try
        {
            int server_port = Integer.parseInt(str_server_port);
            return server_port >= 0 && server_port <= 65535;
        }
        catch (NumberFormatException e)
        {
            System.out.println("Error: The port number must be a positive integer between 0 and 65535.");
            return false;
        }
    }
    private static int getServerPortFromFile(String file_path) throws IOException
    {
        File server_port_file = new File(file_path);
        if (!server_port_file.exists())
        {
            System.out.println("Error: The server port data file at the specified path does not exist. Path: " + server_port_file.getAbsolutePath());
        }
        else 
        {
            try (BufferedReader fileReader = new BufferedReader(new FileReader(server_port_file)))
            {
                String firstLine = fileReader.readLine();
                if (firstLine != null && !firstLine.isEmpty())
                {
                    System.out.println("First line of the server port data file is the port number. Port: " + firstLine);
                    if (isValidPort(firstLine))
                        return Integer.parseInt(firstLine);
                }
                else
                {
                    System.out.println("Error: The server port data file does not contain the port number. Correct the server port data file.");
                }
            }
            catch (IOException e)
            {
                System.err.println("Error reading the server port data file: " + e.toString());
            }
        }
        throw new IOException("\n\tUnable to read valid server port data from the file.");
    }
}