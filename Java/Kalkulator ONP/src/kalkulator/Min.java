package kalkulator;


public class Minimum extends Operator2Arg
{
    public Minimum (Wyrazenie w1, Wyrazenie w2)
    {
        super(w1,w2);
    }

    public double oblicz () {
        return Math.min(arg1.oblicz(),arg2.oblicz());
    }
    public String toString () {
        return "(Minimum z "+arg1+",  "+arg2+")";
    }
}
