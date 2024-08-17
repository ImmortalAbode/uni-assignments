package beans_jsp;

import java.util.ArrayList;

public class MainBean {
    private int evenNegativeSum;
    private int oddPositiveSum;
    private boolean trigger;
    private String numbers;
    private String errorMessage;
    
    public MainBean(){
        evenNegativeSum = 0;
        oddPositiveSum = 0;
        trigger = false;
        numbers = "";
        errorMessage = "";
    }

    /**
     * @return the evenNegativeSum
     */
    public int getEvenNegativeSum() 
    {
        return this.evenNegativeSum;
    }

    /**
     * @return the oddNegativeSum
     */
    public int getOddPositiveSum() 
    {
        return this.oddPositiveSum;
    }
    
    /**
     * @return the numbers
     */
    public boolean getTrigger() {
        return this.trigger;
    }

    /**
     * @return the numbers
     */
    public String getNumbers() {
        return this.numbers;
    }

    /**
     * @return the errorMessage
     */
    public String getErrorMessage() 
    {
        return this.errorMessage;
    }

    /**
     * @param evenNegativeSum the evenNegativeSum to set
     */
    public void setEvenNegativeSum(int evenNegativeSum) 
    {
        this.evenNegativeSum = evenNegativeSum;
    }

    /**
     * @param oddPositiveSum the oddPositiveSum to set
     */
    public void setOddPositiveSum(int oddPositiveSum) 
    {
        this.oddPositiveSum = oddPositiveSum;
    }
    
    /**
     * @param trigger the trigger to set
     */
    public void setTrigger(boolean trigger) {
        this.trigger = trigger;
    }

    /**
     * @param numbers the numbers to set
     */
    public void setNumbers(String numbers) 
    {
        this.numbers = numbers;
    }

    /**
     * @param errorMessage the errorMessage to set
     */
    public void setErrorMessage(String errorMessage) 
    {
        this.errorMessage = errorMessage;
    }
}