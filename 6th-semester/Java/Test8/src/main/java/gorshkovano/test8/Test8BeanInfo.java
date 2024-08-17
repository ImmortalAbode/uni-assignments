package gorshkovano.test8;

import java.beans.*;
public class Test8BeanInfo extends SimpleBeanInfo 
{
    public PropertyDescriptor[] getPropertyDescriptors() 
    {
        try 
        {
            PropertyDescriptor rectangular = new PropertyDescriptor("rectangular", Test8.class);
            PropertyDescriptor pd[] = 
            {
                rectangular
            };
            return pd;
        }
        catch(Exception e) 
        {
            System.out.println("Возникло исключение: " + e);
        }
        return null;
    }
    public static void main(String[] args)
    {
        Test8BeanInfo mf = new Test8BeanInfo();
        mf.getPropertyDescriptors();
    }
}
