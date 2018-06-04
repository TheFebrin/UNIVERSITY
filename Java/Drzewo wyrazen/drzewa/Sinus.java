package drzewa;

public class Sinus extends Operator1Arg
{
    public Sinus(Wyrazenie w1)
    {
        super(w1);
    }
    /**
     *
     * @return obliczenia
     */
    public double oblicz()
    {
        return Math.sin(arg1.oblicz());
    }

    public String toString()
    {
        return "sin ("+arg1+")";
    }
}