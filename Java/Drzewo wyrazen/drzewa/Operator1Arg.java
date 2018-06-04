package drzewa;

public abstract class Operator1Arg extends Wyrazenie
{
    protected final Wyrazenie arg1;

    public Operator1Arg (Wyrazenie arg1)
    {
        if(arg1==null) throw new IllegalArgumentException("Brak wyrazenia");
        this.arg1=arg1;
    }

}