package client;

import compute.Task;
import java.io.Serializable;
import java.math.BigDecimal;


public class NumberSequenceSum implements Task<BigDecimal>, Serializable {
    //Определение версии для сериализации и десериализации.
    private static final long serialVersionUID = 227L;
    //Массив для записи последовательности чисел.
    private final double[] numbers;
    //Передача numbers в this.numbers
    public NumberSequenceSum(double[] numbers) {
        this.numbers = numbers;
    }
    //Проверка чисел на четность/нечетность.
    public static boolean isEvenOrOdd(double num) {
        while (num % 1 != 0){
            num *= 10;
        }
        var integerPart = (int) num;
        return (Math.abs(integerPart) % 2 == 0);
    }
    //Основной метод, реализующий интерфейс.
    @Override
    public BigDecimal[] execute() {
        return computeSum(numbers);
    }
    //Метод для вычисления искомых сумм.
    public static BigDecimal[] computeSum(double[] numbers){
        BigDecimal sumEvenNegative = BigDecimal.ZERO;
        BigDecimal sumOddNegative = BigDecimal.ZERO;
        // Проход по массиву чисел и вычисление суммы чётных и нечётных отрицательных чисел.
        try{
            for (double num : numbers) {
                if (num < 0) {
                    if (isEvenOrOdd(num)) { // Проверка на чётность.
                        sumEvenNegative = sumEvenNegative.add(BigDecimal.valueOf(num));
                    } else { // Если не чётное, значит нечётное.
                        sumOddNegative = sumOddNegative.add(BigDecimal.valueOf(num));
                    }
                }  
            }
        }
        catch (NumberFormatException e){
            System.err.println("NumberFormatException: " + e.getMessage());
        }
        // Возвращение пары сумм чётных и нечётных отрицательных чисел (массивом).
        return new BigDecimal[]{sumEvenNegative, sumOddNegative};
    }
}