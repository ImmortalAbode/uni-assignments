package client;

import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.math.BigDecimal;
import compute.Compute;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;

public class ComputeSubsequence
{
    public static void main(String args[]) 
    {
        if (System.getSecurityManager() == null)
        {
            System.setSecurityManager(new SecurityManager());
        }
        try 
        {
            String name = "Compute";
            Registry registry = LocateRegistry.getRegistry(args[0]);
            Compute comp = (Compute) registry.lookup(name);
            
            // Преобразование строки, содержащей числа, в массив int[]
            String[] strNumbers = args[1].split(" ");
            int[] numbers = new int[strNumbers.length];
            for (int i = 0; i < strNumbers.length; i++) {
                numbers[i] = Integer.parseInt(strNumbers[i]);
            }
            
            Subsequence task = new Subsequence(numbers);
            BigDecimal[] subsequence = comp.executeTask(task);
            System.out.println("Sum of even negative numbers: " + subsequence[0]);
            System.out.println("Sum of odd positive numbers: " + subsequence[1]);
        } 
        catch (NumberFormatException | NotBoundException | RemoteException e) 
        {
            System.err.println("ComputeSubsequence exception:" + e);
        }
    }
}

