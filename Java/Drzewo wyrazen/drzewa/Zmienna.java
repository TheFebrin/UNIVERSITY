package drzewa;

public class Zmienna extends Wyrazenie
{
    public static final Zbior tablicaPar=new Zbior();
    public final String klucz;

    /**
     *
     * @param klucz podajemy klucz
     * @param wartosc podajemy wartosc
     */
    public Zmienna(String klucz,double wartosc)
    {
        Para p=new Para(klucz,wartosc);
        tablicaPar.ustal(p);
        this.klucz=klucz;
    }

    /**
     *
     * @return oblicz
     */
    public double oblicz()
    {
        return tablicaPar.czytaj(klucz);
    }

    /**
     *
     * @return zwraca klucz
     */
    public String toString()
    {
        return klucz;
    }
}