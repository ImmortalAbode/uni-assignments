package client;

import compute.Task;
import java.io.Serializable;
import java.math.BigDecimal;
public class Subsequence implements Task<BigDecimal[]>, Serializable 
{
    //Определение версии для сериализации и десериализации.
    private static final long serialVersionUID = 227L;
    //Массив для последовательности чисел.
    private final int[] numbers;

    public Subsequence(int[] numbers) 
    {
        this.numbers = numbers;
    }

    @Override
    public BigDecimal[] execute() 
    {
        
        BigDecimal[] sums = new BigDecimal[2];
        BigDecimal evenNegativeNumbers = BigDecimal.ZERO;
        BigDecimal oddPositiveNumbers = BigDecimal.ZERO;

        for (int num : numbers) 
        {
            if (num < 0 && num % 2 == 0) 
            {
                evenNegativeNumbers = evenNegativeNumbers.add(BigDecimal.valueOf(num));
            }
            if (num > 0 && num % 2 != 0)
            {
                oddPositiveNumbers = oddPositiveNumbers.add(BigDecimal.valueOf(num));
            }
        }
        sums[0] = evenNegativeNumbers; //сумма четных отрицательных чисел
        sums[1] = oddPositiveNumbers; //сумма нечетных положительных чисел

        return sums;
    }
}