package gorshkovano.test2;
/********** 
* ПРИМЕР 1*
***********/
class Dan 
{
    public int xSup, xSub;
    public boolean b;
    public Dan (int Xsub, int Xsup, boolean B) 
        {
            xSub= Xsub; xSup= Xsup; b= B;
        }
}
//Суперкласс (super class)
class SuperClass 
{
    int x;
    private boolean b;
    public SuperClass (int X, boolean B) 
        {
            x= X; b= B;
        }   
    public boolean getB () 
        {
            return b;
        }
}
// Подкласс (sub class)
class SubClass extends SuperClass 
{
    int x;
    public SubClass (int Xsup, int Xsub, boolean B) // Конструктор
        {
            super (Xsub, B); // Вызов конструктора базового класса
            x = Xsup;
        }
    // Получить объект типа Dan с данными
    public Dan get () 
        {
            return new Dan(x, super.x, super.getB());
        }
    public void get (Dan d) 
        {
            d.xSub= x; d.xSup= super.x; d.b= super.getB();
        }
}

/********** 
* ПРИМЕР 2*
***********/
interface IFunc 
{
    public int getF();
}
interface IConst 
{
    public static final int verConst = 100;
}
class ClassInt implements IFunc, IConst 
{
    public int getF ()
        { 
            return verConst;
        }
}
/********** 
* ПРИМЕР 3*
***********/
/* Интерфейсы и неоднозначность*/
interface IConst1 
{
    static final int verConst = 101;
}
interface IConst2 
{
    int verConst = 102;
}
interface IConst_3 extends IConst1, IConst2 
{
    static final int verConst = 100;
    int get (boolean b);
}
class ClassInt_3 implements IConst_3
{
    public int get (boolean b)
        { 
            return b ? IConst1.verConst : IConst2.verConst;
        }
}
/********** 
* ПРИМЕР 5*
***********/
class MyException extends Exception 
{
    //public MyException () {}
    public String toString () 
        { 
            return "MyException happened";
        }
}
//ОБЩЕЕ ВЫПОЛНЕНИЕ ВСЕХ ПРИМЕРОВ.
public class Test2 
{
    /*К примеру 4*/
    static void Func( ) 
    { 
        int m=10, n=0; n= m/n; 
    }
    static void Func_2() throws MyException 
    {
        int m = 0, n = 10;
        if((m/n) == 0) 
            throw new MyException ();
        System.out.print ("Next");
    }
    public static void main (String[] args) 
    {
        /*ПРИМЕР 1*/
        SuperClass supC = new SuperClass (5, true );// Создать объект суперкласса
        System.out.println ("supC.x= "+ supC.x + " supC.b= " + supC.getB());
        // Создать объект подкласса
        SubClass subC = new SubClass (55, 555, false );
        // Получить объект данных
        Dan d = subC.get();
        System.out.println ("subC.x= "+ d.xSub + " supC.x= "+ d.xSup + " subC.b= " + d.b);
        //Перегруженный метод get()
        Dan d1= new Dan (0, 0, true);
        subC.get(d1);
        System.out.println ("subC.x= "+ d1.xSub +" supC.x= "+ d1.xSup + " subC.b= " + d1.b);
        /*Пример 2*/
        //TestInterface
        ClassInt cI = new ClassInt();
        System.out.println ("verConst= " + cI.getF());
        IFunc iF = cI;
        IConst iC = cI;
        System.out.println ("verConst= " + iF.getF());
        // System.out.println ("verConst= " + iC.getF()); // Error
        // Cannot find 'getF()' in 'IConst'
        System.out.println ("verConst= " + iC.verConst);
        System.out.println ("verConst= " + ClassInt.verConst);
        /*Пример 3*/
        ClassInt_3 cI_3 = new ClassInt_3();
        System.out.print ("cI.verConst= " + cI_3.verConst);
        System.out.println (" ClassInt.verConst= " + ClassInt_3.verConst);
        //--------------
        IConst1 iC1 = cI_3;
        System.out.print ("iC1.verConst= " + iC1.verConst);
        IConst2 iC2 = cI_3;
        System.out.print (" iC2.verConst= " + iC2.verConst);
        IConst_3 iC_3 = cI_3;
        System.out.println (" iC.verConst= " + iC_3.verConst);
        //--------------
        System.out.print ("IConst1.verConst= " + IConst1.verConst);
        System.out.print (" IConst2.verConst= " + IConst2.verConst);
        System.out.println (" IConst.verConst= " + IConst_3.verConst);
        //--------------
        System.out.println ("cI.get(true)= " + cI_3.get(true) + " cI.get(false)= "+ cI_3.get(false));
        /********** 
        * ПРИМЕР 4*
        ***********/
        //TestExc
        try 
        {
            Func();
        }
        catch (ArithmeticException e) 
        {
            System.out.println ("ArithmeticException happened");
        }
        catch (Exception e) 
        {
            System.out.println ("Exception happened");
        }
        finally 
        {
            System.out.println ("finally");
        }
        /*Пример 5*/
        try
        {
            Func_2();
        }
        catch (MyException e) 
        {
            System.out.println (e);
        }
    }
}
