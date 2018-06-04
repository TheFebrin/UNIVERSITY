package drzewa;


public class Logarytmowanie extends Operator2Arg
{
    public Logarytmowanie (Wyrazenie w1, Wyrazenie w2)
    {
        super(w1,w2);
    }

    public double oblicz () {
        return Math.log(arg1.oblicz())/Math.log(arg2.oblicz());
    }
    public String toString () {
        return "(logarytm z "+arg1+" o podstawie "+arg2+")";
    }
}
