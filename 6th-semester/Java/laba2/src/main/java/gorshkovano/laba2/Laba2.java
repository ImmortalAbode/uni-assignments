//Автоматически созданный пакет при создании проекта для его структурирования.
package gorshkovano.laba2;

//Импорт классов для настройки корректного отображения кириллических символов из пакета java.io в NetBeans.
import java.io.PrintStream;
import java.io.UnsupportedEncodingException;

//Создание интерфейса функции для вычисления искомых сумм и обработки исключений при последующей реализации класса.
interface FuncsNumberProcessor
{
    static final int MIN_ARRAY_LENGTH = 5; // Минимальное число элементов массива.
    static final int MAX_ARRAY_LENGTH = 10; // Максимальное число элементов массива.
    static final int MAX_ARRAY_ELEMENT = 100; // Максимальное значение элемента массива.
    void calculateEvenNegativeAndOddPositiveSum(String[] args) throws NotEnoughElementsException, NumericException, TooManyElementsException;
    void handleException(String message);
}
//Создание интерфейса функции для вывода искомых сумм при последующей реализации класса.
interface PrintResultsNumberProcess
{
    void printResults(int sumEvenNegativeNumbers, int sumOddPositiveNumbers);
}

//Исключение: Исходный массив содержит недостаточное количество элементов. Их число меньше указанного.
class NotEnoughElementsException extends Exception
{
    public NotEnoughElementsException(String message)
    {
        super(message);
    }
}

//Исключение: Исходный массив содержит элемент, который больше, чем некоторое заданное число.
class NumericException extends Exception
{
    public NumericException(String message)
    {
        super(message);
    }
}

//Исключение: Исходный массив содержит слишком много элементов. Их число больше указанного.
class TooManyElementsException extends Exception
{
    public TooManyElementsException(String message)
    {
        super(message);
    }
}

//Основной класс, реализующий интерфейсы.
class NumberProcessor implements FuncsNumberProcessor, PrintResultsNumberProcess
{
    //Поля класса.
    private int sumEvenNegativeNumbers = 0;
    private int sumOddPositiveNumbers = 0;
    //Класс имеет конструктор по умолчанию.
    //Методы класса.
    @Override
    public void calculateEvenNegativeAndOddPositiveSum(String[] args) throws NotEnoughElementsException, NumericException, TooManyElementsException
    {
        if (args.length > MAX_ARRAY_LENGTH)
        {
            throw new TooManyElementsException("TooManyElementsException happened: Command line arguments length is greater than " + FuncsNumberProcessor.MAX_ARRAY_LENGTH + ".");
        }
        if (args.length < MIN_ARRAY_LENGTH)
        {
            throw new NotEnoughElementsException("NotEnoughElementsException happened: Command line arguments length is less than " + FuncsNumberProcessor.MIN_ARRAY_LENGTH + ".");
        }
        for (String arg: args)
        {
            try
            {
                int num = Integer.parseInt(arg);
                if (num > MAX_ARRAY_ELEMENT)
                {
                    throw new NumericException("NumericException happened: Command line arguments contain a number that is greater than " + FuncsNumberProcessor.MAX_ARRAY_ELEMENT + ".");
                }
                if (num < 0 && num % 2 == 0)
                {
                    this.sumEvenNegativeNumbers += num;
                }
                if (num > 0 && num % 2 == 1)
                {
                    this.sumOddPositiveNumbers += num;
                }
            }
            catch (NumberFormatException e)
            {
                System.out.println("Unhandled exception happened.");
                System.exit(1);
            }
        }
    }
    @Override
    public void printResults(int sumEvenNegativeNumbers, int sumOddPositiveNumbers){
       System.out.println("Sum of even and negative numbers: " + sumEvenNegativeNumbers);
       System.out.println("Sum of odd and positive numbers: " + sumOddPositiveNumbers);
    }
    @Override
    public void handleException(String message)
    {
        System.out.println(message);
    }
    public int getSumEvenNegativeNumbers()
    {
        return this.sumEvenNegativeNumbers;
    }
    public int getSumOddPositiveNumbers()
    {
        return this.sumOddPositiveNumbers;
    }
}

public class Laba2
{
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
        
        NumberProcessor numberProcessor = new NumberProcessor();
        try
        {
            numberProcessor.calculateEvenNegativeAndOddPositiveSum(args);
            numberProcessor.printResults(numberProcessor.getSumEvenNegativeNumbers(), numberProcessor.getSumOddPositiveNumbers());
        }
        catch (NotEnoughElementsException | NumericException | TooManyElementsException e)
        {
            numberProcessor.handleException(e.getMessage());
        }
    }
}