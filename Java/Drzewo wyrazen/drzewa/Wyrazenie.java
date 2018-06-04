package drzewa;

public abstract class Wyrazenie
{
    public abstract double oblicz();

    /**
     *
     * @param wyr wyrazenie
     * @return metoda sumująca wyrażenia
     */
    public static double sumuj (Wyrazenie... wyr)
    {
        double suma =0;
        for(int i=0;i<wyr.length;i++)
        {
            suma+=wyr[i].oblicz();
        }

        return suma;
    }

    /**
     *
     * @param wyr mnozy wyrazenie
     * @return metoda mnożąca wyrażenia
     */
    public static double pomnoz (Wyrazenie... wyr)
    {
        double iloczyn =1;
        for(int i=0;i<wyr.length;i++)
        {
            iloczyn*=wyr[i].oblicz();
        }

        return iloczyn;
    }
}