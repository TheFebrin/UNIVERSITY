
package drzewa;

public class Stala extends Wyrazenie
{
    public final double liczba;

    /**
     *
     * @param a liczba
     */
    public Stala (double a)
    {
        liczba=a;
    }

    public double oblicz () {
        return liczba;
    }
    public String toString () {
        return String.valueOf(liczba);
    }
}