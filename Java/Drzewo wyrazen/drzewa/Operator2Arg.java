package drzewa;

public abstract class Operator2Arg extends Operator1Arg
{
    protected final Wyrazenie arg2;

    public Operator2Arg(Wyrazenie w1,Wyrazenie w2)
    {
        super(w1);
        if(w2==null) throw new IllegalArgumentException("Brak wyrazenia");
        arg2=w2;
    }
}