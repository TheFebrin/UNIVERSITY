package drzewa;

public class Odwrotnosc extends Operator1Arg
{
    public Odwrotnosc(Wyrazenie w1)
    {
        super(w1);
    }

    public double oblicz()
    {
        return 1/(arg1.oblicz());
    }

    public String toString()
    {
        return "Odwrotnosc to("+arg1+")";
    }
}