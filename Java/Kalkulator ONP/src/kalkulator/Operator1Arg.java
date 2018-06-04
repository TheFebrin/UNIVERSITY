package kalkulator;

public abstract class Operator1Arg extends Funkcja implements Funkcyjny
{

    public static double[] argument=new double[2];
    public int licznik;

    public Operator1Arg ()
    {
       licznik=0;
    }

    public int arnosc()
    {
        return 1;
    }

    public int brakujaceArgumenty()
    {
        return arnosc-licznik;
    }

    public void dodajArgument(double arg)
    {
        argument[licznik]=arg;
        licznik++;
    }
}