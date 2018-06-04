package drzewa;

public class Przeciwienstwo extends Operator1Arg
{
    public Przeciwienstwo(Wyrazenie w1)
    {
        super(w1);
    }
    /**
     *
     * @return obliczenia
     */
    public double oblicz()
    {
        return -(arg1.oblicz());
    }
    public String toString()
    {
        return "-("+arg1+")";
    }
}