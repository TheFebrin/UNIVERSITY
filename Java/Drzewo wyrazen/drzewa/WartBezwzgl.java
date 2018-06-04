package drzewa;

public class WartBezwzgl extends Operator1Arg
{
    public WartBezwzgl (Wyrazenie w1) {
        super(w1);
    }

    /**
     *
     * @return obliczenia
     */
    public double oblicz () {
        return Math.abs(arg1.oblicz());
    }
    public String toString () {
        return "|"+arg1+"|";
    }
}