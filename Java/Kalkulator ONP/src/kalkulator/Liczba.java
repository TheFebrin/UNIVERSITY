package kalkulator;

public class Liczba extends Operand{

    public double liczba;

    public Liczba(double liczba)
    {
        this.liczba=liczba;
    }

    public double ObliczWartosc()
    {
        return liczba;
    }
}