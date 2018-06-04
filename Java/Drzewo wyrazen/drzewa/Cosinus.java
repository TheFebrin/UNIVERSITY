package drzewa;

public class Cosinus extends Operator1Arg
{
    public Cosinus(Wyrazenie w1)
    {
        super(w1);
    }

    public double oblicz()
    {
        return Math.cos(arg1.oblicz());
    }

    /**
     *
     * @return
     */
    public String toString()
    {
        return "cos ("+arg1+")";
    }
}