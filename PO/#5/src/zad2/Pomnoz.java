package zad2;

public class Pomnoz extends Operator{

    public Pomnoz(Wyrazenie w1, Wyrazenie w2)
    {
        super(w1,w2);
    }
    public double oblicz()
    {
        return w1.oblicz()*w2.oblicz();
    }
}
