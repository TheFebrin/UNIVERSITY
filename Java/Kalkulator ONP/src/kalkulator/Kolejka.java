package kalkulator;

public class Kolejka<T> extends Lista
{
    public Kolejka(T in)
    {
        super(in);
    }

    public void AddData(T in)
    {
        End(new Wezel(in));
    }

}