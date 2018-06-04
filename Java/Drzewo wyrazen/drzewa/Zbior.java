package drzewa;


public class Zbior  //przechowuje pary
{
    private int index=0;
    public Para[]tablicaPar;
    Para brakPary=new Para("brak",0);

    /**
     * konstruktor Zbioru
     */
    public Zbior()
    {
        Para[]tablicaPar=new Para[50];
    }


    /**
     *
     * @param kl szuka zadanego klucza w zbiorze
     * @return metoda szuka pary z okreslonym kluczem
     */
    public Para szukaj (String kl)
    {
        for(int i=0;i<index;i++)
        {
            if(tablicaPar[i].klucz.equals(kl))
            {
                return tablicaPar[i];
            }
        }
        return brakPary;
    }

    /**
     *
     * @param p wstawia pare p
     * @throws IllegalArgumentException poza zakresem zbioru
     */
    public void wstaw (Para p) throws IllegalArgumentException
    {
        if(index>=50) throw new IllegalArgumentException("Poza zakresem zbioru!");
        else
        {
            if(szukaj(p.klucz)==brakPary)
            {
                tablicaPar[index]=p;
                index++;
            }
            else
            {
                throw new IllegalArgumentException("Ta para juz jest w zbiorze");
            }
        }
    }

    /**
     *
     * @param kl zadany klucz
     * @return metoda odszukuje pare i zwraca wartosc związaną z kluczem
     * @throws IllegalArgumentException klucza nie ma w zbiorze
     */
    public double czytaj (String kl) throws IllegalArgumentException
    {
        if(szukaj(kl).equals("brak")) throw new IllegalArgumentException("Pary z danym kluczem nie ma w zbiorze");
        else
        {
            return szukaj(kl).getWartosc();
        }

    }

    /**
     * metoda wstawia do zbioru nowa albo aktualizuje istniejącą pare
     * @param p para p
     * @throws IllegalArgumentException brak pary
     */
    public void ustal (Para p) throws IllegalArgumentException
    {
        if(szukaj(p.klucz).equals("brak")) wstaw(p);
        else
        {
            szukaj(p.klucz).setWartosc(p.getWartosc());
        }
    }

    /**
     *
     * @return metoda podaje ile par jest przechowywanych w zbiorze
     */
    public int ile ()
    {
        return index;
    }

    /**
     * metoda usuwa wszystkie pary ze zbioru
     */
    public void czysc ()
    {
        index=0;
        tablicaPar=new Para[50];
    }
}
