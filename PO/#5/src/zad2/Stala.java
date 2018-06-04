package zad2;

public class Stala extends Wyrazenie
{
    double wartosc;

    public Stala(double wartosc)
    {
        this.wartosc=wartosc;
    }

    public double oblicz()
    {
        return wartosc;
    }
}
