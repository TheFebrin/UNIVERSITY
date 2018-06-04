package kalkulator;

public class Stos<T> extends Lista
{
    public Stos(T in)
{
    super(in);
}

    public void AddData(T in)
{
    Beggining(new Wezel(in));
}

}