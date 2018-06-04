package drzewa;

public class Arctan extends Operator1Arg
{
    public Arctan(Wyrazenie w1)
    {
        super(w1);
    }

    public double oblicz()
    {
        return Math.atan(arg1.oblicz());
    }

    public String toString()
    {
        return "arctan ("+arg1+")";
    }
}