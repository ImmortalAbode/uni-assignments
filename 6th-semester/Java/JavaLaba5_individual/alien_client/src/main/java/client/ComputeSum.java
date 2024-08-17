package client;

import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.math.BigDecimal;
import compute.Compute;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;

public class ComputeSum {
    public static void main(String args[]) {
	if (System.getSecurityManager() == null) {
		System.setSecurityManager(new SecurityManager());
	}
        try {
            String name = "Compute";
            Registry registry = LocateRegistry.getRegistry(args[0]);
            Compute comp = (Compute) registry.lookup(name);
            
            //Преобразование второго аргумента строки в массив чисел. 
            String[] numbersAsString = args[1].split("\\s+");
            double[] numbers = new double[numbersAsString.length];
            for (int i = 0; i < numbersAsString.length; i++) {
                numbers[i] = Double.parseDouble(numbersAsString[i]);
            }

            NumberSequenceSum task = new NumberSequenceSum(numbers);
            BigDecimal[] sums = comp.executeTask(task);
            System.out.println("Sum of even and negative numbers: " + sums[0]);
            System.out.println("Summ of odd and negative numbers: " + sums[1]);
        } catch (NumberFormatException | NotBoundException | RemoteException e) {
            System.err.println("ComputeSum exception:" + e.getMessage());
        }
    }
}