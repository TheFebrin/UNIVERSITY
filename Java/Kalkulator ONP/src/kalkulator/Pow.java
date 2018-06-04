package kalkulator;


public class Potegowanie extends Operator2Arg
{
    public Potegowanie (Wyrazenie w1, Wyrazenie w2)
    {
        super(w1,w2);
    }

    /**
     *
     * @return obliczenia
     */

    public double oblicz () {
        return Math.pow(arg1.oblicz(),arg2.oblicz());
    }
    public String toString ()
    {
        return "("+arg1+" do potegi "+arg2+")";
    }
}
