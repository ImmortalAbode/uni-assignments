package client;

import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.math.BigDecimal;
import compute.Compute;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;

public class ComputePi 
{
    public static void main(String args[]) 
    {
        try 
        {
            String name = "Compute";
            Registry registry = LocateRegistry.getRegistry(args[0]);
            Compute comp = (Compute) registry.lookup(name);
            Pi task = new Pi(Integer.parseInt(args[1]));
            BigDecimal pi = comp.executeTask(task);
            System.out.println(pi);
        } 
        catch (NumberFormatException | NotBoundException | RemoteException e) 
        {
            System.err.println("ComputePi exception:");
        }
    }
}
