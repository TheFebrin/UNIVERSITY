package drzewa;


public class Dodawanie extends Operator2Arg
{
    public Dodawanie (Wyrazenie w1, Wyrazenie w2)
    {
        super(w1,w2);
    }

    public double oblicz () {
        return arg1.oblicz()+arg2.oblicz();
    }
    public String toString () {
        return "("+arg1+" + "+arg2+")";
    }
}
