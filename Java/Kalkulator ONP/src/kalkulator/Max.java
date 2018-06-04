package kalkulator;


public class Maksimum extends Operator2Arg
{
    public Maksimum (Wyrazenie w1, Wyrazenie w2)
    {
        super(w1,w2);
    }

    public double oblicz () {
        return Math.max(arg1.oblicz(),arg2.oblicz());
    }
    public String toString () {
        return "(Maksimum z "+arg1+",  "+arg2+")";
    }
}
