package drzewa;

public class Para //przechowuje pary klucz–wartosc
{
    public final String klucz;
    private double wartosc;

    /**
     *
     * @param klucz -zadany klucz
     * @param wartosc - przypisana do niego wartosc
     */
    public Para(String klucz,double wartosc)
    {
        this.klucz=klucz;
        this.wartosc=wartosc;
    }

    /**
     *
     * @return - zwraca wartosc
     */
    public double getWartosc()
    {
        return this.wartosc;
    }

    /**
     *
     * @param d ustawia wartosc na d
     */
    public  void setWartosc(double d)
    {
        this.wartosc=d;
    }

    /**
     *
     * @return -zwraca klucz i przypisana mu wartosc
     */
    public String toString()
    {
        return("klucz= "+this.klucz+", wartosc="+this.getWartosc());
    }

    /**
     *
     * @param p porownuje z Para p
     * @return jezeli klucze sa takie same zwraca prawde
     */
    public boolean equals(Para p) //pary sa rowne gdy maja takie same klucze
    {
        if(this.klucz==p.klucz)
        {
            return true;
        }
        else return false;
    }
}
